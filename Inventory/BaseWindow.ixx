module;

#include "Gtkmm.hpp"

export module Inventory:BaseWindow;

import :Helpers;

namespace Inventory
{
    class BaseWindow : public Gtk::Window
    {
      public:
        using Gtk::Window::Window;

        BaseWindow() noexcept = default;

        virtual void InitializeComponents() noexcept
        {
            set_decorated(true);
            set_default_size(800, 500);

            if ( m_CenterOnScreen )
            {
                signal_map().connect(sigc::mem_fun(*this, &BaseWindow::ScheduleCenterWindowOnScreen));
            }
        }

        void CenterWindowOnScreen() noexcept
        {
            auto* native = gtk_widget_get_native(GTK_WIDGET(gobj()));

            if ( native == nullptr )
            {
                return;
            }

            auto* surface = gtk_native_get_surface(native);

            if ( surface == nullptr )
            {
                return;
            }

            if ( !GDK_IS_WIN32_SURFACE(surface) )
            {
                return;
            }

            Win32::CenterWindowOnScreen(gdk_win32_surface_get_handle(surface));
        }

      protected:
        void SetCenterOnScreen(const bool value) noexcept
        {
            m_CenterOnScreen = value;
        }

      private:
        void ScheduleCenterWindowOnScreen() noexcept
        {
            if ( m_WasCentered )
            {
                return;
            }

            m_WasCentered = true;

            Glib::signal_timeout().connect(
                [this]() -> bool {
                    CenterWindowOnScreen();
                    return false;
                },
                1   // Interval in milliseconds
            );
        }

      private:
        bool m_CenterOnScreen { true };
        bool m_WasCentered { false };
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
