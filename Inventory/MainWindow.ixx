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

export module Inventory:MainWindow;

export class MainWindow : public Gtk::Window
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
        m_Label.set_text("Hello, World!");
        set_child(m_Label);
    }

    void CenterWindowOnScreen() { }

  private:
    Gtk::Label m_Label;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif
