<#
.SYNOPSIS
Genera archivos .c y .h desde un archivo .gresource.xml usando glib-compile-resources de VCPKG.

.DESCRIPTION
Este script busca glib-compile-resources.exe en:
1. -ToolPath, si lo pasas manualmente.
2. La carpeta vcpkg_installed del proyecto.
3. La variable de entorno VCPKG_ROOT.
4. Una búsqueda recursiva limitada desde la carpeta actual.

.PARAMETER ResourceXmlPath
Ruta del archivo .gresource.xml a compilar.

.PARAMETER OutputDirectory
Carpeta donde se generarán los archivos .c y .h.

.PARAMETER CName
Nombre base C usado por glib-compile-resources. Por defecto: inventory_resources.

.PARAMETER SourceDir
Directorio base para resolver rutas relativas dentro del .gresource.xml.
Si no se indica, se usa la carpeta padre del archivo .gresource.xml.

.PARAMETER Triplet
Triplet de VCPKG. Por defecto: x64-windows.

.PARAMETER ToolPath
Ruta explícita a glib-compile-resources.exe, si deseas indicarla manualmente.

.EXAMPLE
.\Generate-GResource.ps1 `
  -ResourceXmlPath .\Resources\inventory.gresource.xml `
  -OutputDirectory .\Resources

.EXAMPLE
.\Generate-GResource.ps1 `
  -ResourceXmlPath .\Resources\inventory.gresource.xml `
  -OutputDirectory .\Generated `
  -SourceDir . `
  -CName inventory_resources

.EXAMPLE
.\Generate-GResource.ps1 `
  -ResourceXmlPath .\Resources\inventory.gresource.xml `
  -OutputDirectory .\Resources `
  -ToolPath .\vcpkg_installed\x64-windows\tools\glib\glib-compile-resources.exe
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$ResourceXmlPath,

    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$OutputDirectory,

    [Parameter(Mandatory = $false)]
    [ValidateNotNullOrEmpty()]
    [string]$CName = "inventory_resources",

    [Parameter(Mandatory = $false)]
    [string]$SourceDir,

    [Parameter(Mandatory = $false)]
    [ValidateNotNullOrEmpty()]
    [string]$Triplet = "x64-windows",

    [Parameter(Mandatory = $false)]
    [string]$ToolPath
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Resolve-FullPath {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Path
    )

    $executionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($Path)
}

function Find-GlibCompileResources {
    param(
        [string]$ExplicitToolPath,
        [string]$Triplet
    )

    if (-not [string]::IsNullOrWhiteSpace($ExplicitToolPath)) {
        $resolvedToolPath = Resolve-FullPath $ExplicitToolPath

        if (Test-Path $resolvedToolPath -PathType Leaf) {
            return $resolvedToolPath
        }

        throw "No se encontró glib-compile-resources.exe en ToolPath: $resolvedToolPath"
    }

    $candidatePaths = New-Object System.Collections.Generic.List[string]
    $currentDirectory = (Get-Location).Path

    $candidatePaths.Add((Join-Path $currentDirectory "vcpkg_installed\$Triplet\tools\glib\glib-compile-resources.exe"))

    if ($env:VCPKG_ROOT) {
        $candidatePaths.Add((Join-Path $env:VCPKG_ROOT "installed\$Triplet\tools\glib\glib-compile-resources.exe"))
    }

    foreach ($candidate in $candidatePaths) {
        if (Test-Path $candidate -PathType Leaf) {
            return $candidate
        }
    }

    $localSearch = Get-ChildItem `
        -Path $currentDirectory `
        -Recurse `
        -Filter "glib-compile-resources.exe" `
        -File `
        -ErrorAction SilentlyContinue |
        Select-Object -First 1

    if ($null -ne $localSearch) {
        return $localSearch.FullName
    }

    if ($env:VCPKG_ROOT -and (Test-Path $env:VCPKG_ROOT -PathType Container)) {
        $vcpkgSearch = Get-ChildItem `
            -Path $env:VCPKG_ROOT `
            -Recurse `
            -Filter "glib-compile-resources.exe" `
            -File `
            -ErrorAction SilentlyContinue |
            Select-Object -First 1

        if ($null -ne $vcpkgSearch) {
            return $vcpkgSearch.FullName
        }
    }

    throw @"
No se encontró glib-compile-resources.exe.

Soluciones:
1. Verifica que gtkmm/glib esté instalado con VCPKG.
2. Revisa tu triplet actual. Ejemplo: x64-windows, x64-windows-static.
3. Pasa la ruta manualmente usando -ToolPath.
"@
}

try {
    $resolvedXmlPath = Resolve-FullPath $ResourceXmlPath

    if (-not (Test-Path $resolvedXmlPath -PathType Leaf)) {
        throw "No existe el archivo XML: $resolvedXmlPath"
    }

    $resolvedOutputDirectory = Resolve-FullPath $OutputDirectory

    if (-not (Test-Path $resolvedOutputDirectory -PathType Container)) {
        New-Item -ItemType Directory -Path $resolvedOutputDirectory | Out-Null
    }

    if ([string]::IsNullOrWhiteSpace($SourceDir)) {
        $resolvedSourceDir = Split-Path -Path $resolvedXmlPath -Parent
    }
    else {
        $resolvedSourceDir = Resolve-FullPath $SourceDir
    }

    if (-not (Test-Path $resolvedSourceDir -PathType Container)) {
        throw "No existe el SourceDir: $resolvedSourceDir"
    }

    $tool = Find-GlibCompileResources -ExplicitToolPath $ToolPath -Triplet $Triplet

    $sourceOutputPath = Join-Path $resolvedOutputDirectory "$CName.c"
    $headerOutputPath = Join-Path $resolvedOutputDirectory "$CName.h"

    Write-Host "Usando herramienta:" -ForegroundColor Cyan
    Write-Host "  $tool"

    Write-Host "Archivo XML:" -ForegroundColor Cyan
    Write-Host "  $resolvedXmlPath"

    Write-Host "SourceDir:" -ForegroundColor Cyan
    Write-Host "  $resolvedSourceDir"

    Write-Host "Generando source:" -ForegroundColor Cyan
    Write-Host "  $sourceOutputPath"

    & $tool `
        $resolvedXmlPath `
        "--target=$sourceOutputPath" `
        "--generate-source" `
        "--manual-register" `
        "--c-name" $CName `
        "--sourcedir=$resolvedSourceDir"

    if ($LASTEXITCODE -ne 0) {
        throw "Falló la generación del archivo .c. Código de salida: $LASTEXITCODE"
    }

    Write-Host "Generando header:" -ForegroundColor Cyan
    Write-Host "  $headerOutputPath"

    & $tool `
        $resolvedXmlPath `
        "--target=$headerOutputPath" `
        "--generate-header" `
        "--manual-register" `
        "--c-name" $CName `
        "--sourcedir=$resolvedSourceDir"

    if ($LASTEXITCODE -ne 0) {
        throw "Falló la generación del archivo .h. Código de salida: $LASTEXITCODE"
    }

    Write-Host ""
    Write-Host "Recursos generados correctamente." -ForegroundColor Green
    Write-Host "Source: $sourceOutputPath"
    Write-Host "Header: $headerOutputPath"
}
catch {
    Write-Host ""
    Write-Host "Error:" -ForegroundColor Red
    Write-Host $_.Exception.Message -ForegroundColor Red
    exit 1
}
