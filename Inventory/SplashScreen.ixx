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
        {
            InitializeComponents();
        }

        virtual void InitializeComponents() noexcept override
        {
            BaseWindow::InitializeComponents();

            set_title("Inventory");
            set_default_size(1000, 500);
            set_decorated(false);
            set_resizable(false);

            m_Root.set_margin_top(32);
            m_Root.set_margin_bottom(32);
            m_Root.set_margin_start(32);
            m_Root.set_margin_end(32);
            m_Root.set_spacing(16);

            m_Title.set_text("Inventory");
            m_Title.add_css_class("title-1");
            m_Title.set_halign(Gtk::Align::CENTER);

            m_Subtitle.set_text("Inicializando sistema...");
            m_Subtitle.add_css_class("dim-label");
            m_Subtitle.set_halign(Gtk::Align::CENTER);

            m_Spinner.set_halign(Gtk::Align::CENTER);
            m_Spinner.start();

            m_ProgressBar.set_pulse_step(0.15);
            m_ProgressBar.pulse();

            m_Root.append(m_Title);
            m_Root.append(m_Subtitle);
            m_Root.append(m_Spinner);
            m_Root.append(m_ProgressBar);

            set_child(m_Root);
        }

      private:
        Gtk::Box         m_Root;
        Gtk::Label       m_Title;
        Gtk::Label       m_Subtitle;
        Gtk::Spinner     m_Spinner;
        Gtk::ProgressBar m_ProgressBar;
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
