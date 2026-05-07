module;

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#pragma warning(push, 0)

#include <gtkmm.h>

export module Inventory:Application;

import :MainWindow;

export namespace Inventory
{
    int32_t Main(const std::vector<char*>& args) noexcept
    {
        auto application = Gtk::Application::create("com.inventory.app");
        return application->make_window_and_run<MainWindow>(args.size(), const_cast<char**>(args.data()));
    }
}   // namespace Inventory

#pragma warning(pop)
