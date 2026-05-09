# Uso de `GResource.ps1`

Este script genera archivos `.c` y `.h` a partir de un archivo `.gresource.xml` usando `glib-compile-resources.exe` instalado por VCPKG/GTK.

En este proyecto, el script está ubicado en:

```text
<ProjectDir>/Tools/GResource.ps1
```

Su objetivo principal es compilar recursos GTK, por ejemplo imágenes del `SplashScreen`, para que queden embebidos dentro de la aplicación.

---

## Estructura esperada del proyecto

Estructura recomendada:

```text
<ProjectDir>/
  Assets/
    Images/
      SplashScreen.png
      AcrossTec_AppIcon.ico
      AcrossTec_AppSmallIcon.ico

  Resources/
    Gtk/
      SplashScreen.gresource.xml
      SplashScreen_gresource.c
      SplashScreen_gresource.h

    Win/
      Resource.h
      AppIcon.rc

  Tools/
    GResource.ps1
```

Para el `SplashScreen`, el archivo XML debe estar en:

```text
<ProjectDir>/Resources/Gtk/SplashScreen.gresource.xml
```

Ejemplo del XML:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<gresources>
  <gresource prefix="/com/acrosstec/inventory">
    <file alias="SplashScreen.png">Assets/Images/SplashScreen.png</file>
  </gresource>
</gresources>
```

La ruta final del recurso será:

```text
/com/acrosstec/inventory/SplashScreen.png
```

Y puede cargarse desde GTKmm así:

```cpp
m_Background.set_resource("/com/acrosstec/inventory/SplashScreen.png");
```

---

## Uso recomendado para este proyecto

Desde PowerShell, ubicado en `<ProjectDir>`:

```powershell
.\Tools\GResource.ps1 `
  -ResourceXmlPath .\Resources\Gtk\SplashScreen.gresource.xml `
  -OutputDirectory .\Resources\Gtk `
  -SourceDir . `
  -CName SplashScreen_gresource
```

Esto genera:

```text
<ProjectDir>/Resources/Gtk/SplashScreen_gresource.c
<ProjectDir>/Resources/Gtk/SplashScreen_gresource.h
```

---

## Parámetros del script

### `-ResourceXmlPath`

Obligatorio.

Ruta del archivo `.gresource.xml` que se desea compilar.

Ejemplo:

```powershell
-ResourceXmlPath .\Resources\Gtk\SplashScreen.gresource.xml
```

---

### `-OutputDirectory`

Obligatorio.

Carpeta donde se generarán los archivos `.c` y `.h`.

Ejemplo:

```powershell
-OutputDirectory .\Resources\Gtk
```

---

### `-CName`

Opcional.

Nombre base usado por `glib-compile-resources` para generar los símbolos C.

Valor por defecto:

```text
inventory_resources
```

Para este proyecto se recomienda:

```powershell
-CName SplashScreen_gresource
```

Con ese valor se generan funciones como:

```cpp
SplashScreen_gresource_get_resource();
SplashScreen_gresource_register_resource();
SplashScreen_gresource_unregister_resource();
```

Y archivos con estos nombres:

```text
SplashScreen_gresource.c
SplashScreen_gresource.h
```

---

### `-SourceDir`

Opcional.

Directorio base usado para resolver las rutas internas del `.gresource.xml`.

En este proyecto debe usarse:

```powershell
-SourceDir .
```

Esto es importante porque el XML referencia la imagen así:

```xml
<file alias="SplashScreen.png">Assets/Images/SplashScreen.png</file>
```

Esa ruta parte desde `<ProjectDir>`, no desde `Resources/Gtk`.

---

### `-Triplet`

Opcional.

Triplet de VCPKG usado para buscar `glib-compile-resources.exe`.

Valor por defecto:

```text
x64-windows
```

Ejemplo:

```powershell
-Triplet x64-windows
```

Si usas otro triplet, por ejemplo estático:

```powershell
-Triplet x64-windows-static
```

---

### `-ToolPath`

Opcional.

Ruta explícita a `glib-compile-resources.exe`.

Úsalo si el script no encuentra la herramienta automáticamente.

Ejemplo:

```powershell
-ToolPath .\vcpkg_installed\x64-windows\tools\glib\glib-compile-resources.exe
```

---

## Ejemplos de uso

### Generar recursos del SplashScreen

```powershell
.\Tools\GResource.ps1 `
  -ResourceXmlPath .\Resources\Gtk\SplashScreen.gresource.xml `
  -OutputDirectory .\Resources\Gtk `
  -SourceDir . `
  -CName SplashScreen_gresource
```

---

### Usar un triplet específico

```powershell
.\Tools\GResource.ps1 `
  -ResourceXmlPath .\Resources\Gtk\SplashScreen.gresource.xml `
  -OutputDirectory .\Resources\Gtk `
  -SourceDir . `
  -CName SplashScreen_gresource `
  -Triplet x64-windows
```

---

### Pasar manualmente la ruta de `glib-compile-resources.exe`

```powershell
.\Tools\GResource.ps1 `
  -ResourceXmlPath .\Resources\Gtk\SplashScreen.gresource.xml `
  -OutputDirectory .\Resources\Gtk `
  -SourceDir . `
  -CName SplashScreen_gresource `
  -ToolPath .\vcpkg_installed\x64-windows\tools\glib\glib-compile-resources.exe
```

---

## Si PowerShell bloquea la ejecución

Si aparece un error como:

```text
La ejecución de scripts está deshabilitada en este sistema.
```

Habilita la ejecución solo para la sesión actual:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
```

Luego vuelve a ejecutar el script.

También puedes ejecutar el script en una sola llamada así:

```powershell
powershell.exe -ExecutionPolicy Bypass -File .\Tools\GResource.ps1 `
  -ResourceXmlPath .\Resources\Gtk\SplashScreen.gresource.xml `
  -OutputDirectory .\Resources\Gtk `
  -SourceDir . `
  -CName SplashScreen_gresource
```

---

## Archivos generados

El script genera dos archivos:

```text
<CName>.c
<CName>.h
```

Para:

```powershell
-CName SplashScreen_gresource
```

se generan:

```text
SplashScreen_gresource.c
SplashScreen_gresource.h
```

---

## Agregar archivos generados al proyecto Visual Studio

Los archivos generados deben estar incluidos en el proyecto:

```text
Resources/Gtk/SplashScreen_gresource.c
Resources/Gtk/SplashScreen_gresource.h
```

El archivo `.c` debe compilarse junto con la aplicación.

En Visual Studio:

```text
Right click sobre el proyecto
  Add
  Existing Item
  Resources/Gtk/SplashScreen_gresource.c
  Resources/Gtk/SplashScreen_gresource.h
```

Recomendación para el `.c`:

```text
Compile As: Compile as C Code (/TC)
```

---

## Uso desde C++/GTKmm

Incluye el header generado:

```cpp
#include "Resources/Gtk/SplashScreen_gresource.h"
```

Registra el recurso antes de usarlo:

```cpp
SplashScreen_gresource_register_resource();
```

Desregístralo cuando la aplicación termine:

```cpp
SplashScreen_gresource_unregister_resource();
```

Ejemplo típico dentro de la clase `Application`:

```cpp
void on_startup() override
{
    Gtk::Application::on_startup();
    SplashScreen_gresource_register_resource();
}
```

Y al finalizar:

```cpp
~Application() override
{
    SplashScreen_gresource_unregister_resource();
}
```

---

## Uso del recurso en el SplashScreen

Después de registrar el recurso, la imagen se carga así:

```cpp
m_Background.set_resource("/com/acrosstec/inventory/SplashScreen.png");
```

La ruta debe coincidir con:

```xml
<gresource prefix="/com/acrosstec/inventory">
  <file alias="SplashScreen.png">Assets/Images/SplashScreen.png</file>
</gresource>
```

---

## Notas importantes

- Ejecuta el script desde `<ProjectDir>`.
- Usa `-SourceDir .` cuando las rutas del XML estén basadas en la raíz del proyecto.
- El valor de `-CName` define tanto los nombres de los archivos generados como los nombres de las funciones C.
- Si cambias la imagen, vuelve a ejecutar el script para regenerar el `.c` y `.h`.
- Si cambias el alias o el prefix del XML, también debes actualizar la ruta usada en `set_resource(...)`.
- Los archivos generados deben recompilarse para que los cambios queden embebidos en el ejecutable.
