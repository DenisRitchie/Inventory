module;

#include "Gtkmm.hpp"

export module Inventory:MainWindow;

import :Helpers;
import :BaseWindow;

export namespace Inventory
{
    class MainWindow : public BaseWindow
    {
      public:
        MainWindow() noexcept
        {
            InitializeComponents();
        }

        virtual void InitializeComponents() noexcept override
        {
            SetCenterOnScreen(false);
            BaseWindow::InitializeComponents();

            set_title("AcrossTec Inventory");
            set_default_size(1000, 700);

            maximize();

            m_Label.set_text("Hello, World!");
            set_child(m_Label);
        }

      private:
        Gtk::Label m_Label;
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
