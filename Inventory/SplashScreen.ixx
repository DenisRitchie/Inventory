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
        {
            InitializeComponents();
        }

        virtual void InitializeComponents() noexcept override
        {
            SetCenterOnScreen(true);
            BaseWindow::InitializeComponents();

            set_title("AcrossTec Inventory");
            set_default_size(1000, 500);
            set_size_request(1000, 500);
            set_decorated(false);
            set_resizable(false);

            // Load from file:
            // m_Background.set_filename("Assets/Images/SplashScreen.png");
            // m_Background.set_size_request(1000, 500);
            // m_Background.set_content_fit(Gtk::ContentFit::FILL);

            // Load from resource:
            m_Background.set_resource("/com/acrosstec/inventory/SplashScreen.png");
            m_Background.set_size_request(1000, 500);
            m_Background.set_content_fit(Gtk::ContentFit::FILL);
            m_Background.set_alternative_text("AcrossTec Inventory Splash Screen");

            set_child(m_Background);
        }

      private:
        Gtk::Picture m_Background;
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
