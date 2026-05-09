[CmdletBinding()]
param(
    [string]$ProjectDir = (Get-Location).Path,

    [string]$Triplet = "x64-windows",

    [string]$ThemePackage = "Orchis",

    [switch]$All,

    [switch]$ListAvailable,

    [switch]$CleanTemp
)

$ErrorActionPreference = "Stop"

$githubApiUrl = "https://api.github.com/repos/vinceliuice/Orchis-theme/contents/release?ref=master"

function Write-Step {
    param([string]$Message)

    Write-Host ""
    Write-Host "==> $Message" -ForegroundColor Cyan
}

function Assert-CommandExists {
    param([string]$Command)

    if (-not (Get-Command $Command -ErrorAction SilentlyContinue)) {
        throw "No se encontró '$Command'. Verifica que esté disponible en PATH."
    }
}

function Get-ThemePackageName {
    param([string]$Name)

    if ($Name.EndsWith(".tar.xz")) {
        return $Name
    }

    return "$Name.tar.xz"
}

function Get-OrchisReleasePackages {
    Write-Step "Consultando paquetes disponibles en Orchis release"

    $headers = @{
        "User-Agent" = "Inventory-Orchis-Theme-Installer"
        "Accept"     = "application/vnd.github+json"
    }

    $items = Invoke-RestMethod -Uri $githubApiUrl -Headers $headers -Method Get

    $packages = $items |
        Where-Object {
            $_.type -eq "file" -and
            $_.name -like "*.tar.xz"
        } |
        Sort-Object name

    if (-not $packages -or $packages.Count -eq 0) {
        throw "No se encontraron paquetes .tar.xz en la carpeta release de Orchis."
    }

    return $packages
}

function Install-OrchisPackage {
    param(
        [Parameter(Mandatory = $true)]
        $Package,

        [Parameter(Mandatory = $true)]
        [string]$TempRoot,

        [Parameter(Mandatory = $true)]
        [string]$ThemesRoot
    )

    $packageName = $Package.name
    $downloadUrl = $Package.download_url

    $archivePath = Join-Path $TempRoot $packageName
    $extractRoot = Join-Path $TempRoot ([System.IO.Path]::GetFileNameWithoutExtension([System.IO.Path]::GetFileNameWithoutExtension($packageName)))

    Write-Step "Descargando $packageName"

    Write-Host "URL: $downloadUrl"
    Write-Host "Destino: $archivePath"

    & curl.exe `
        -L `
        --fail `
        --retry 5 `
        --connect-timeout 30 `
        --max-time 600 `
        -o $archivePath `
        $downloadUrl

    if ($LASTEXITCODE -ne 0) {
        throw "Falló la descarga de $downloadUrl"
    }

    if (-not (Test-Path $archivePath)) {
        throw "No se descargó el archivo: $archivePath"
    }

    Write-Step "Extrayendo $packageName"

    Remove-Item $extractRoot -Recurse -Force -ErrorAction SilentlyContinue
    New-Item -ItemType Directory -Force $extractRoot | Out-Null

    & tar.exe -xf $archivePath -C $extractRoot

    if ($LASTEXITCODE -ne 0) {
        throw "Falló la extracción del archivo: $archivePath"
    }

    Write-Step "Instalando temas GTK 4 desde $packageName"

    $gtkCssFiles = Get-ChildItem $extractRoot -Recurse -Filter "gtk.css" |
        Where-Object { $_.Directory.Name -eq "gtk-4.0" }

    if (-not $gtkCssFiles -or $gtkCssFiles.Count -eq 0) {
        Write-Warning "El paquete $packageName no contiene carpetas gtk-4.0\gtk.css."
        return @()
    }

    $installedThemes = New-Object System.Collections.Generic.List[string]

    foreach ($cssFile in $gtkCssFiles) {
        $themeFolder = $cssFile.Directory.Parent.FullName
        $themeName = Split-Path $themeFolder -Leaf
        $destination = Join-Path $ThemesRoot $themeName

        Write-Host "Instalando tema: $themeName"
        Write-Host "Desde: $themeFolder"
        Write-Host "Hacia: $destination"

        Remove-Item $destination -Recurse -Force -ErrorAction SilentlyContinue
        Copy-Item $themeFolder $destination -Recurse -Force

        $installedThemes.Add($themeName)
    }

    return $installedThemes
}

Write-Step "Validando herramientas"

Assert-CommandExists "curl.exe"
Assert-CommandExists "tar.exe"

$projectRoot = (Resolve-Path $ProjectDir).Path
$vcpkgRuntime = Join-Path $projectRoot "vcpkg_installed\$Triplet"
$themesRoot = Join-Path $vcpkgRuntime "share\themes"
$tempRoot = Join-Path $projectRoot ".theme-downloads\orchis"

if (-not (Test-Path $vcpkgRuntime)) {
    throw "No existe el runtime de vcpkg: $vcpkgRuntime"
}

New-Item -ItemType Directory -Force $themesRoot | Out-Null
New-Item -ItemType Directory -Force $tempRoot | Out-Null

$availablePackages = Get-OrchisReleasePackages

if ($ListAvailable) {
    Write-Step "Paquetes disponibles"

    $availablePackages | ForEach-Object {
        Write-Host " - $($_.name)"
    }

    exit 0
}

if ($All) {
    $packagesToInstall = $availablePackages
}
else {
    $themePackageName = Get-ThemePackageName $ThemePackage

    $selectedPackage = $availablePackages |
        Where-Object { $_.name -ieq $themePackageName } |
        Select-Object -First 1

    if (-not $selectedPackage) {
        Write-Host ""
        Write-Host "No se encontró el paquete: $themePackageName" -ForegroundColor Red
        Write-Host ""
        Write-Host "Paquetes disponibles:" -ForegroundColor Yellow

        $availablePackages | ForEach-Object {
            Write-Host " - $($_.name)"
        }

        throw "Paquete no encontrado."
    }

    $packagesToInstall = @($selectedPackage)
}

$allInstalledThemes = New-Object System.Collections.Generic.List[string]

foreach ($package in $packagesToInstall) {
    $installedThemes = Install-OrchisPackage `
        -Package $package `
        -TempRoot $tempRoot `
        -ThemesRoot $themesRoot

    foreach ($theme in $installedThemes) {
        if (-not $allInstalledThemes.Contains($theme)) {
            $allInstalledThemes.Add($theme)
        }
    }
}

Write-Step "Temas instalados en $themesRoot"

$allInstalledThemes | Sort-Object | ForEach-Object {
    Write-Host " - $_"
}

if ($CleanTemp) {
    Write-Step "Limpiando temporales"
    Remove-Item $tempRoot -Recurse -Force -ErrorAction SilentlyContinue
}

Write-Host ""
Write-Host "Listo. Puedes usar alguno de estos valores con GTK_THEME:" -ForegroundColor Green

$allInstalledThemes | Sort-Object | ForEach-Object {
    Write-Host "g_setenv(`"GTK_THEME`", `"$_`", true);"
}