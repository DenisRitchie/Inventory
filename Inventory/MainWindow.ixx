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
            BaseWindow::InitializeComponents();

            set_title("Inventory");
            set_default_size(800, 500);

            m_Label.set_text("Hello, World!");
            set_child(m_Label);
        }

      private:
        Gtk::Label m_Label;
    };
}   // namespace Inventory

#include "Gtkmm-end.hpp"
