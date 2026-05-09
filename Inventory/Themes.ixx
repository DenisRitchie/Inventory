module;

#include <array>
#include <string_view>

export module Inventory:Themes;

export namespace Inventory::Themes::Orchis
{
    using namespace std::string_view_literals;

    inline constexpr std::string_view Orchis             = "Orchis"sv;
    inline constexpr std::string_view OrchisDark         = "Orchis-Dark"sv;
    inline constexpr std::string_view OrchisLight        = "Orchis-Light"sv;
    inline constexpr std::string_view OrchisCompact      = "Orchis-Compact"sv;
    inline constexpr std::string_view OrchisDarkCompact  = "Orchis-Dark-Compact"sv;
    inline constexpr std::string_view OrchisLightCompact = "Orchis-Light-Compact"sv;

    inline constexpr std::string_view OrchisPurple             = "Orchis-Purple"sv;
    inline constexpr std::string_view OrchisPurpleDark         = "Orchis-Purple-Dark"sv;
    inline constexpr std::string_view OrchisPurpleLight        = "Orchis-Purple-Light"sv;
    inline constexpr std::string_view OrchisPurpleCompact      = "Orchis-Purple-Compact"sv;
    inline constexpr std::string_view OrchisPurpleDarkCompact  = "Orchis-Purple-Dark-Compact"sv;
    inline constexpr std::string_view OrchisPurpleLightCompact = "Orchis-Purple-Light-Compact"sv;

    inline constexpr std::string_view OrchisPink             = "Orchis-Pink"sv;
    inline constexpr std::string_view OrchisPinkDark         = "Orchis-Pink-Dark"sv;
    inline constexpr std::string_view OrchisPinkLight        = "Orchis-Pink-Light"sv;
    inline constexpr std::string_view OrchisPinkCompact      = "Orchis-Pink-Compact"sv;
    inline constexpr std::string_view OrchisPinkDarkCompact  = "Orchis-Pink-Dark-Compact"sv;
    inline constexpr std::string_view OrchisPinkLightCompact = "Orchis-Pink-Light-Compact"sv;

    inline constexpr std::string_view OrchisRed             = "Orchis-Red"sv;
    inline constexpr std::string_view OrchisRedDark         = "Orchis-Red-Dark"sv;
    inline constexpr std::string_view OrchisRedLight        = "Orchis-Red-Light"sv;
    inline constexpr std::string_view OrchisRedCompact      = "Orchis-Red-Compact"sv;
    inline constexpr std::string_view OrchisRedDarkCompact  = "Orchis-Red-Dark-Compact"sv;
    inline constexpr std::string_view OrchisRedLightCompact = "Orchis-Red-Light-Compact"sv;

    inline constexpr std::string_view OrchisOrange             = "Orchis-Orange"sv;
    inline constexpr std::string_view OrchisOrangeDark         = "Orchis-Orange-Dark"sv;
    inline constexpr std::string_view OrchisOrangeLight        = "Orchis-Orange-Light"sv;
    inline constexpr std::string_view OrchisOrangeCompact      = "Orchis-Orange-Compact"sv;
    inline constexpr std::string_view OrchisOrangeDarkCompact  = "Orchis-Orange-Dark-Compact"sv;
    inline constexpr std::string_view OrchisOrangeLightCompact = "Orchis-Orange-Light-Compact"sv;

    inline constexpr std::string_view OrchisYellow             = "Orchis-Yellow"sv;
    inline constexpr std::string_view OrchisYellowDark         = "Orchis-Yellow-Dark"sv;
    inline constexpr std::string_view OrchisYellowLight        = "Orchis-Yellow-Light"sv;
    inline constexpr std::string_view OrchisYellowCompact      = "Orchis-Yellow-Compact"sv;
    inline constexpr std::string_view OrchisYellowDarkCompact  = "Orchis-Yellow-Dark-Compact"sv;
    inline constexpr std::string_view OrchisYellowLightCompact = "Orchis-Yellow-Light-Compact"sv;

    inline constexpr std::string_view OrchisGreen             = "Orchis-Green"sv;
    inline constexpr std::string_view OrchisGreenDark         = "Orchis-Green-Dark"sv;
    inline constexpr std::string_view OrchisGreenLight        = "Orchis-Green-Light"sv;
    inline constexpr std::string_view OrchisGreenCompact      = "Orchis-Green-Compact"sv;
    inline constexpr std::string_view OrchisGreenDarkCompact  = "Orchis-Green-Dark-Compact"sv;
    inline constexpr std::string_view OrchisGreenLightCompact = "Orchis-Green-Light-Compact"sv;

    inline constexpr std::string_view OrchisTeal             = "Orchis-Teal"sv;
    inline constexpr std::string_view OrchisTealDark         = "Orchis-Teal-Dark"sv;
    inline constexpr std::string_view OrchisTealLight        = "Orchis-Teal-Light"sv;
    inline constexpr std::string_view OrchisTealCompact      = "Orchis-Teal-Compact"sv;
    inline constexpr std::string_view OrchisTealDarkCompact  = "Orchis-Teal-Dark-Compact"sv;
    inline constexpr std::string_view OrchisTealLightCompact = "Orchis-Teal-Light-Compact"sv;

    inline constexpr std::string_view OrchisGrey             = "Orchis-Grey"sv;
    inline constexpr std::string_view OrchisGreyDark         = "Orchis-Grey-Dark"sv;
    inline constexpr std::string_view OrchisGreyLight        = "Orchis-Grey-Light"sv;
    inline constexpr std::string_view OrchisGreyCompact      = "Orchis-Grey-Compact"sv;
    inline constexpr std::string_view OrchisGreyDarkCompact  = "Orchis-Grey-Dark-Compact"sv;
    inline constexpr std::string_view OrchisGreyLightCompact = "Orchis-Grey-Light-Compact"sv;

    inline constexpr std::array<std::string_view, 54> All {
        Orchis,       OrchisDark,       OrchisLight,       OrchisCompact,       OrchisDarkCompact,       OrchisLightCompact,
        OrchisPurple, OrchisPurpleDark, OrchisPurpleLight, OrchisPurpleCompact, OrchisPurpleDarkCompact, OrchisPurpleLightCompact,
        OrchisPink,   OrchisPinkDark,   OrchisPinkLight,   OrchisPinkCompact,   OrchisPinkDarkCompact,   OrchisPinkLightCompact,
        OrchisRed,    OrchisRedDark,    OrchisRedLight,    OrchisRedCompact,    OrchisRedDarkCompact,    OrchisRedLightCompact,
        OrchisOrange, OrchisOrangeDark, OrchisOrangeLight, OrchisOrangeCompact, OrchisOrangeDarkCompact, OrchisOrangeLightCompact,
        OrchisYellow, OrchisYellowDark, OrchisYellowLight, OrchisYellowCompact, OrchisYellowDarkCompact, OrchisYellowLightCompact,
        OrchisGreen,  OrchisGreenDark,  OrchisGreenLight,  OrchisGreenCompact,  OrchisGreenDarkCompact,  OrchisGreenLightCompact,
        OrchisTeal,   OrchisTealDark,   OrchisTealLight,   OrchisTealCompact,   OrchisTealDarkCompact,   OrchisTealLightCompact,
        OrchisGrey,   OrchisGreyDark,   OrchisGreyLight,   OrchisGreyCompact,   OrchisGreyDarkCompact,   OrchisGreyLightCompact
    };
}   // namespace Inventory::Themes::Orchis
