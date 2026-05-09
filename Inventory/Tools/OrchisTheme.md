# Instalación de Orchis Theme para GTKMM 4 + Visual Studio 2026 + vcpkg

Este documento explica cómo usar el script:

```text
Tools\Install-OrchisTheme.ps1
```

para descargar e instalar **Orchis Theme** dentro del runtime local de `vcpkg` de tu proyecto C++.

El objetivo es que los temas queden instalados en:

```text
$(ProjectDir)vcpkg_installed\x64-windows\share\themes
```

y que Visual Studio copie automáticamente esos temas al directorio de salida, por ejemplo:

```text
$(OutDir)share\themes
```

De esa forma, GTK podrá cargar el tema desde el mismo directorio donde se ejecuta tu aplicación.

---

## 1. Estructura esperada del proyecto

Ejemplo de estructura actual:

```text
Inventory/
│
├── Inventory.vcxproj
├── vcpkg.json
├── Tools/
│   └── Install-OrchisTheme.ps1
│
├── vcpkg_installed/
│   └── x64-windows/
│       ├── bin/
│       ├── include/
│       ├── lib/
│       └── share/
│           └── themes/
│
└── ...
```

Después de instalar Orchis, deberías tener algo como:

```text
Inventory/
└── vcpkg_installed/
    └── x64-windows/
        └── share/
            └── themes/
                ├── Orchis/
                │   └── gtk-4.0/
                │       └── gtk.css
                │
                ├── Orchis-Dark/
                │   └── gtk-4.0/
                │       └── gtk.css
                │
                └── Orchis-Purple/
                    └── gtk-4.0/
                        └── gtk.css
```

---

## 2. Requisitos

Necesitas tener disponible:

```text
PowerShell
curl.exe
tar.exe
```

En Windows 10/11 moderno normalmente `curl.exe` y `tar.exe` ya vienen incluidos.

Puedes verificarlo con:

```powershell
curl.exe --version
tar.exe --version
```

También debes tener instalado `gtkmm` mediante `vcpkg` en tu proyecto:

```powershell
vcpkg install
```

o, si lo haces manualmente:

```powershell
vcpkg install gtkmm:x64-windows
```

---

## 3. Ubicación del script

Crea esta carpeta:

```text
Tools
```

Luego coloca el script aquí:

```text
Tools\Install-OrchisTheme.ps1
```

La ruta final debe quedar así:

```text
Inventory\Tools\Install-OrchisTheme.ps1
```

---

## 4. Abrir PowerShell en la raíz del proyecto

Abre PowerShell y entra a la raíz del proyecto donde está tu `.vcxproj`:

```powershell
cd "C:\Projects\C++\Inventory\Inventory"
```

Desde ahí puedes ejecutar el script usando rutas relativas.

---

## 5. Ver los paquetes disponibles

Para listar todos los paquetes `.tar.xz` disponibles en el release de Orchis:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ListAvailable
```

Ejemplo de salida esperada:

```text
==> Paquetes disponibles
 - Orchis.tar.xz
 - Orchis-Green.tar.xz
 - Orchis-Grey.tar.xz
 - Orchis-Orange.tar.xz
 - Orchis-Pink.tar.xz
 - Orchis-Purple.tar.xz
 - Orchis-Red.tar.xz
 - Orchis-Teal.tar.xz
 - Orchis-Yellow.tar.xz
```

La lista real puede cambiar según el repositorio de Orchis.

---

## 6. Instalar el tema principal Orchis

Para instalar el paquete principal:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis
```

El script descargará:

```text
Orchis.tar.xz
```

y copiará los temas encontrados a:

```text
vcpkg_installed\x64-windows\share\themes
```

---

## 7. Instalar una variante específica

Puedes instalar una variante concreta, por ejemplo:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Purple
```

Otros ejemplos:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Green
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Red
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Teal
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Yellow
```

No es necesario escribir la extensión `.tar.xz`.

Esto:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Purple
```

equivale a:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Purple.tar.xz
```

---

## 8. Instalar todos los temas disponibles

Para descargar e instalar todos los paquetes `.tar.xz` disponibles:

```powershell
.\Tools\Install-OrchisTheme.ps1 -All
```

Esto puede instalar varias carpetas de temas dentro de:

```text
vcpkg_installed\x64-windows\share\themes
```

Ejemplo:

```text
Orchis
Orchis-Dark
Orchis-Light
Orchis-Purple
Orchis-Purple-Dark
Orchis-Green
Orchis-Green-Dark
...
```

Los nombres exactos dependen del contenido de los paquetes descargados.

---

## 9. Limpiar archivos temporales después de instalar

El script usa una carpeta temporal:

```text
.theme-downloads\orchis
```

Si deseas borrar los archivos temporales al final, usa:

```powershell
.\Tools\Install-OrchisTheme.ps1 -All -CleanTemp
```

O para un solo tema:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis -CleanTemp
```

---

## 10. Cambiar el triplet

Por defecto el script usa:

```text
x64-windows
```

Si necesitas otro triplet, puedes pasarlo así:

```powershell
.\Tools\Install-OrchisTheme.ps1 -Triplet x64-windows-static -ThemePackage Orchis
```

Para tu proyecto actual con `gtkmm` dinámico, lo recomendado es:

```text
x64-windows
```

---

## 11. Cambiar el directorio del proyecto

Por defecto, el script asume que lo ejecutas desde la raíz del proyecto.

También puedes pasar el proyecto explícitamente:

```powershell
.\Tools\Install-OrchisTheme.ps1 `
  -ProjectDir "C:\Projects\C++\Inventory\Inventory" `
  -ThemePackage Orchis
```

---

## 12. Resumen de comandos principales

Listar paquetes disponibles:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ListAvailable
```

Instalar Orchis:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis
```

Instalar Orchis Purple:

```powershell
.\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis-Purple
```

Instalar todos los paquetes disponibles:

```powershell
.\Tools\Install-OrchisTheme.ps1 -All
```

Instalar todos y limpiar temporales:

```powershell
.\Tools\Install-OrchisTheme.ps1 -All -CleanTemp
```

---

## 13. Configurar Visual Studio para copiar todos los temas

Para que los temas se copien automáticamente a la carpeta de salida, agrega este bloque al `.vcxproj`, antes de:

```xml
</Project>
```

Bloque recomendado:

```xml
<ItemGroup>
  <GtkThemeFiles Include="$(ProjectDir)vcpkg_installed\x64-windows\share\themes\**\*.*" />
</ItemGroup>

<Target Name="CopyGtkThemesToOutput" AfterTargets="Build">
  <Message Importance="High" Text="Copying GTK themes to $(OutDir)share\themes" />

  <Copy
    SourceFiles="@(GtkThemeFiles)"
    DestinationFiles="@(GtkThemeFiles->'$(OutDir)share\themes\%(RecursiveDir)%(Filename)%(Extension)')"
    SkipUnchangedFiles="true"
    Condition="'@(GtkThemeFiles)' != ''" />
</Target>
```

Este target copia todo lo que exista en:

```text
$(ProjectDir)vcpkg_installed\x64-windows\share\themes
```

hacia:

```text
$(OutDir)share\themes
```

Conservando la estructura de carpetas.

---

## 14. Resultado esperado en Debug

Después de compilar en Debug, deberías tener algo parecido a:

```text
C:\Projects\C++\Inventory\x64\Debug\Inventory.exe
C:\Projects\C++\Inventory\x64\Debug\share\themes\Orchis\gtk-4.0\gtk.css
C:\Projects\C++\Inventory\x64\Debug\share\themes\Orchis-Dark\gtk-4.0\gtk.css
```

---

## 15. Resultado esperado en Release

Después de compilar en Release:

```text
C:\Projects\C++\Inventory\x64\Release\Inventory.exe
C:\Projects\C++\Inventory\x64\Release\share\themes\Orchis\gtk-4.0\gtk.css
C:\Projects\C++\Inventory\x64\Release\share\themes\Orchis-Dark\gtk-4.0\gtk.css
```

---

## 16. Configurar GTK desde código

Como los temas se copian al directorio de salida, debes decirle a GTK que busque sus datos desde la carpeta donde está el `.exe`.

Ejemplo de configuración:

```cpp
static void ConfigureGtkRuntime(int argc, char** argv)
{
    const auto executableDirectory = GetExecutableDirectory(argc, argv);
    const auto dataPrefix = executableDirectory.string();

    g_setenv("GTK_DATA_PREFIX", dataPrefix.c_str(), true);
    g_setenv("GTK_THEME", "Orchis", true);
    g_setenv("GDK_BACKEND", "win32", true);
    g_setenv("GTK_CSD", "0", true);
}
```

Ejemplo completo sin usar WinAPI:

```cpp
#include <filesystem>

static std::filesystem::path GetExecutableDirectory(int argc, char** argv)
{
    if (argc > 0 && argv != nullptr && argv[0] != nullptr)
    {
        return std::filesystem::absolute(
            std::filesystem::path(argv[0])
        ).parent_path();
    }

    return std::filesystem::current_path();
}

static void ConfigureGtkRuntime(int argc, char** argv)
{
    const auto executableDirectory = GetExecutableDirectory(argc, argv);
    const auto dataPrefix = executableDirectory.string();

    g_setenv("GTK_DATA_PREFIX", dataPrefix.c_str(), true);
    g_setenv("GTK_THEME", "Orchis", true);
    g_setenv("GDK_BACKEND", "win32", true);
    g_setenv("GTK_CSD", "0", true);
}
```

Debe llamarse antes de crear `Gtk::Application`:

```cpp
ConfigureGtkRuntime(argc, argv);

auto app = Gtk::Application::create("com.inventory.app");
```

---

## 17. Cambiar el tema desde código

Si instalaste varios temas, puedes cambiar el valor de `GTK_THEME`.

Ejemplo:

```cpp
g_setenv("GTK_THEME", "Orchis", true);
```

Tema oscuro:

```cpp
g_setenv("GTK_THEME", "Orchis-Dark", true);
```

Tema púrpura:

```cpp
g_setenv("GTK_THEME", "Orchis-Purple", true);
```

Tema púrpura oscuro:

```cpp
g_setenv("GTK_THEME", "Orchis-Purple-Dark", true);
```

El nombre debe coincidir con la carpeta existente en:

```text
share\themes
```

Por ejemplo:

```text
share\themes\Orchis-Purple-Dark
```

se usa así:

```cpp
g_setenv("GTK_THEME", "Orchis-Purple-Dark", true);
```

---

## 18. Verificar si el tema se copió bien

Puedes revisar manualmente la carpeta de salida:

```text
$(OutDir)share\themes
```

Por ejemplo:

```text
C:\Projects\C++\Inventory\x64\Debug\share\themes
```

Debe contener carpetas como:

```text
Orchis
Orchis-Dark
Orchis-Purple
```

Cada tema válido para GTK 4 debe tener:

```text
gtk-4.0\gtk.css
```

---

## 19. Problemas comunes

### El tema no se aplica

Verifica que `GTK_DATA_PREFIX` apunte a la carpeta donde está el `.exe`.

Si tu ejecutable está aquí:

```text
C:\Projects\C++\Inventory\x64\Debug\Inventory.exe
```

entonces GTK debe buscar aquí:

```text
C:\Projects\C++\Inventory\x64\Debug\share\themes
```

Por eso `GTK_DATA_PREFIX` debe ser:

```text
C:\Projects\C++\Inventory\x64\Debug
```

---

### El nombre del tema no coincide

Si tienes:

```text
share\themes\Orchis-Dark
```

debes usar:

```cpp
g_setenv("GTK_THEME", "Orchis-Dark", true);
```

No uses:

```cpp
g_setenv("GTK_THEME", "Dark", true);
```

ni:

```cpp
g_setenv("GTK_THEME", "Orchis:dark", true);
```

a menos que esa variante esté realmente soportada por el tema.

---

### No se copian los temas al compilar

Verifica que el target `CopyGtkThemesToOutput` esté dentro del archivo `.vcxproj`, antes de:

```xml
</Project>
```

También verifica que existan archivos aquí:

```text
$(ProjectDir)vcpkg_installed\x64-windows\share\themes
```

Si esa carpeta está vacía, primero ejecuta el script.

---

### PowerShell bloquea el script

Si Windows bloquea la ejecución de scripts, puedes ejecutarlo así:

```powershell
powershell -ExecutionPolicy Bypass -File .\Tools\Install-OrchisTheme.ps1 -ThemePackage Orchis
```

O para todos:

```powershell
powershell -ExecutionPolicy Bypass -File .\Tools\Install-OrchisTheme.ps1 -All
```

---

## 20. Flujo recomendado completo

Primero instala todos los temas:

```powershell
cd "C:\Projects\C++\Inventory\Inventory"

powershell -ExecutionPolicy Bypass -File .\Tools\Install-OrchisTheme.ps1 -All
```

Luego compila el proyecto en Visual Studio.

Después verifica que se haya copiado:

```text
C:\Projects\C++\Inventory\x64\Debug\share\themes
```

Finalmente en el código, antes de crear `Gtk::Application`:

```cpp
ConfigureGtkRuntime(argc, argv);

auto app = Gtk::Application::create("com.inventory.app");
```

---

## 21. Recomendación para producción

Para desarrollo, está bien instalar los temas en:

```text
vcpkg_installed\x64-windows\share\themes
```

y copiarlos con MSBuild al `$(OutDir)`.

Para producción, el instalador final debe incluir:

```text
Inventory.exe
DLLs de GTK/vcpkg
share\themes
share\icons
etc\gtk-4.0
```

La carpeta final de instalación debería quedar parecida a:

```text
Inventory/
│
├── Inventory.exe
├── gtk-4-1.dll
├── gtkmm-4.0.dll
├── glib-2.0-0.dll
├── ...
│
└── share/
    └── themes/
        └── Orchis/
            └── gtk-4.0/
                └── gtk.css
```

Así tu aplicación no dependerá de que el cliente tenga instalado GTK ni Orchis globalmente.
