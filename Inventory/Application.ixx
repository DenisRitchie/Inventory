module;

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#pragma warning(push, 0)

#include <gtkmm.h>

#include <span>
#include <spanstream>
#include <string>
#include <memory>

export module Inventory:Application;

import :MainWindow;

namespace Inventory
{
    [[nodiscard]] std::unique_ptr<char*[]> GetArgv(const std::span<std::string> values) noexcept
    {
        const auto size   = values.size();
        auto       result = std::make_unique<char*[]>(size);

        for ( size_t i = 0; i < size; ++i )
        {
            result[i] = const_cast<char*>(values[i].c_str());
        }

        return result;
    }

    export int32_t Main(const std::span<std::string> args) noexcept
    {
        g_setenv("GTK_CSD", "0", true);
        g_setenv("GDK_BACKEND", "win32", true);

        const auto argv = GetArgv(args);

        auto application = Gtk::Application::create("com.inventory.app");
        return application->make_window_and_run<MainWindow>(args.size(), argv.get());
    }
}   // namespace Inventory

#pragma warning(pop)
