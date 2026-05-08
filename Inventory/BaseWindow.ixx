module;

#include "Gtkmm.hpp"
#include <filesystem>

export module Inventory:BaseWindow;

import :Helpers;

namespace Inventory
{
    class BaseWindow : public Gtk::ApplicationWindow
    {
      public:
        using Gtk::ApplicationWindow::ApplicationWindow;

        BaseWindow() noexcept = default;

        virtual void InitializeComponents() noexcept
        {
            // Asegura que la ventana tenga bordes y barra de título.
            set_decorated(true);

            // Establece un tamaño predeterminado para la ventana al mostrarla por primera vez.
            set_default_size(800, 500);

            // Conecta el controlador de eventos para configurar la ventana nativa después de que se haya creado.
            signal_map().connect(sigc::mem_fun(*this, &BaseWindow::ScheduleNativeWindowConfiguration));
        }

        HWND GetNativeHandle() const noexcept
        {
            auto* native = gtk_widget_get_native(GTK_WIDGET(gobj()));

            if ( native == nullptr )
            {
                return nullptr;
            }

            auto* surface = gtk_native_get_surface(native);

            if ( surface == nullptr )
            {
                return nullptr;
            }

            if ( !GDK_IS_WIN32_SURFACE(surface) )
            {
                return nullptr;
            }

            return gdk_win32_surface_get_handle(surface);
        }

        void CenterWindowOnScreen() const noexcept
        {
            Win32::CenterWindowOnScreen(GetNativeHandle());
        }

        void SetRuntimeWindowIcon(const std::filesystem::path& icon_path) noexcept
        {
            SetRuntimeWindowIcon(icon_path, icon_path);
        }

        void SetRuntimeWindowIcon(const std::filesystem::path& large_icon_path, const std::filesystem::path& small_icon_path) noexcept
        {
            ApplyRuntimeWindowIcon(GetNativeHandle(), large_icon_path, small_icon_path);
        }

      protected:
        void SetCenterOnScreen(const bool value) noexcept
        {
            // Permite configurar si la ventana se centrará en la pantalla al aplicarse la configuración nativa.
            m_CenterOnScreen = value;
        }

      private:
        void ScheduleNativeWindowConfiguration() noexcept
        {
            // Evita configurar la ventana nativa varias veces si se emite la señal map() más de una vez.
            if ( m_WasConfigured )
            {
                return;
            }

            // Evita configurar la ventana nativa varias veces si se emite la señal map() más de una vez.
            m_WasConfigured = true;

            // Usa un timeout para asegurarse de que la ventana nativa esté completamente creada antes de intentar configurarla.
            Glib::signal_timeout().connect(
                [this]() -> bool {   // Lambda para configurar la ventana nativa después de un breve retraso
                    ApplyNativeWindowConfiguration();
                    return false;    // No repetir el timeout
                },
                1                    // Interval in milliseconds
            );
        }

        void ApplyNativeWindowConfiguration() const noexcept
        {
            HWND hwnd = GetNativeHandle();

            if ( hwnd == nullptr )
            {
                return;
            }

            Win32::SetWindowIcon(hwnd);

            if ( m_CenterOnScreen )
            {
                Win32::CenterWindowOnScreen(hwnd);
            }
        }

        void ApplyRuntimeWindowIcon(HWND hwnd, const std::filesystem::path& LargeIconPath, const std::filesystem::path& SmallIconPath) noexcept
        {
            std::filesystem::path large_icon_path = LargeIconPath;
            std::filesystem::path small_icon_path = SmallIconPath;

            const auto executable_directory = Win32::GetExecutableDirectory();

            if ( large_icon_path.is_relative() )
            {
                large_icon_path = executable_directory / large_icon_path;
            }

            if ( small_icon_path.is_relative() )
            {
                small_icon_path = executable_directory / small_icon_path;
            }

            Win32::SetWindowIconFromFile(hwnd, large_icon_path, small_icon_path);
        }

      private:
        bool m_CenterOnScreen { true };
        bool m_WasConfigured { false };
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
