module;

#include "Gtkmm.hpp"

export module Inventory:SplashScreen;

import :BaseWindow;

export namespace Inventory
{
    class SplashScreen : public BaseWindow
    {
      public:
        SplashScreen() noexcept
          : m_Root(Gtk::Orientation::VERTICAL)
          , m_Card(Gtk::Orientation::VERTICAL)
        {
            InitializeComponents();
        }

        virtual void InitializeComponents() noexcept override
        {
            BaseWindow::InitializeComponents();
            LoadStyles();

            set_title("AcrossTec Inventory");

            // La ventana es un poco más grande para que la sombra no se recorte.
            set_default_size(1030, 520);
            set_size_request(1030, 520);

            set_decorated(false);
            set_resizable(false);

            add_css_class("splash-window");

            m_Root.add_css_class("splash-root");
            m_Root.set_margin_top(5);
            m_Root.set_margin_bottom(10);
            m_Root.set_margin_start(5);
            m_Root.set_margin_end(10);
            m_Root.set_halign(Gtk::Align::CENTER);
            m_Root.set_valign(Gtk::Align::CENTER);

            m_Card.add_css_class("splash-card");
            m_Card.set_size_request(1000, 500);
            m_Card.set_overflow(Gtk::Overflow::HIDDEN);

            // Si estás usando GResource:
            m_Background.set_resource("/com/acrosstec/inventory/SplashScreen.png");

            // Si todavía estás usando archivo físico, usa esta línea en vez de set_resource:
            // m_Background.set_filename("Assets/Images/SplashScreen.png");

            m_Background.set_size_request(1000, 500);
            m_Background.set_content_fit(Gtk::ContentFit::FILL);
            m_Background.set_alternative_text("AcrossTec Inventory Splash Screen");

            m_Card.append(m_Background);
            m_Root.append(m_Card);

            set_child(m_Root);
        }

      private:
        void LoadStyles() noexcept
        {
            m_CssProvider = Gtk::CssProvider::create();

            m_CssProvider->load_from_data(
                R"css(
                    window.splash-window {
                        background: transparent;
                    }

                    .splash-root {
                        background: transparent;
                    }

                    .splash-card {
                        background: #061225;
                        border-radius: 24px;
                        box-shadow: 10px 4px 18px rgba(0, 18, 58, 0.72);
                    }
                )css"
            );

            auto display = Gdk::Display::get_default();

            if ( display )
            {
                Gtk::StyleContext::add_provider_for_display(display, m_CssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            }
        }

      private:
        Gtk::Box                       m_Root;
        Gtk::Box                       m_Card;
        Gtk::Picture                   m_Background;
        Glib::RefPtr<Gtk::CssProvider> m_CssProvider;
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
