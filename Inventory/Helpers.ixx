module;

#include "Gtkmm.hpp"

#include <vector>
#include <string>
#include <string_view>

export module Inventory:Helpers;

export import :Win32;
export import :Themes;

export namespace Inventory
{
    bool ApplyGtkTheme(const std::string_view theme_name, Gtk::Widget* widget_to_redraw = nullptr) noexcept
    {
        auto settings = Gtk::Settings::get_default();

        if ( not settings )
        {
            return false;
        }

        settings->property_gtk_theme_name() = theme_name.data();

        if ( widget_to_redraw )
        {
            widget_to_redraw->queue_draw();
        }

        return true;
    }
}   // namespace Inventory

#include "Gtkmm-end.hpp"
