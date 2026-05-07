module;

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)
#endif

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gdk/win32/gdkwin32.h>

export module Inventory:MainWindow;

import :Helpers;

export namespace Inventory
{
    class MainWindow : public Gtk::Window
    {
      public:
        MainWindow() noexcept
        {
            InitializeComponents();
        }

        void InitializeComponents() noexcept
        {
            set_title("Inventory");
            set_default_size(800, 500);
            set_decorated(true);

            m_Label.set_text("Hello, World!");
            set_child(m_Label);

            signal_map().connect(sigc::mem_fun(*this, &MainWindow::ScheduleCenterWindowOnScreen));
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
        Gtk::Label m_Label;
        bool       m_WasCentered { false };
    };
}   // namespace Inventory

#ifdef _MSC_VER
#pragma warning(pop)
#endif
