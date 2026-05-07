module;

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <shellapi.h>

#include <vector>
#include <cstdint>
#include <string>
#include <string_view>

export module Inventory:Win32;

export namespace Inventory::Win32
{
    std::string              WCharToUtf8(const std::wstring_view text) noexcept;
    std::vector<std::string> GetCommandLineArguments() noexcept;
    void                     CenterWindowOnScreen(HWND hwnd) noexcept;
}   // namespace Inventory::Win32

std::string Inventory::Win32::WCharToUtf8(const std::wstring_view text) noexcept
{
    if ( text.empty() )
    {
        return { };
    }

    const int32_t size_needed = WideCharToMultiByte(CP_UTF8, 0, text.data(), -1, nullptr, 0, nullptr, nullptr);

    if ( size_needed <= 0 )
    {
        return { };
    }

    std::string result(size_needed - 1, '\0');

    WideCharToMultiByte(CP_UTF8, 0, text.data(), -1, result.data(), size_needed, nullptr, nullptr);

    return result;
}

std::vector<std::string> Inventory::Win32::GetCommandLineArguments() noexcept
{
    std::vector<std::string> result { };

    int32_t wide_argc = 0;
    LPWSTR* wide_argv = CommandLineToArgvW(GetCommandLineW(), &wide_argc);

    if ( wide_argv == nullptr || wide_argc <= 0 )
    {
        return result;
    }

    result.reserve(wide_argc);

    for ( int32_t i = 0; i < wide_argc; ++i )
    {
        result.emplace_back(WCharToUtf8(wide_argv[i]));
    }

    LocalFree(wide_argv);
    return result;
}

void Inventory::Win32::CenterWindowOnScreen(HWND hwnd) noexcept
{
    if ( hwnd == nullptr || not IsWindow(hwnd) )
    {
        return;
    }

    RECT window_rect { };

    if ( not GetWindowRect(hwnd, &window_rect) )
    {
        return;
    }

    const int32_t window_width  = window_rect.right - window_rect.left;
    const int32_t window_height = window_rect.bottom - window_rect.top;

    const HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);

    if ( monitor == nullptr )
    {
        return;
    }

    //
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-monitorinfoexw
    //
    MONITORINFOEXW monitor_info { };
    monitor_info.cbSize = sizeof(MONITORINFOEXW);

    if ( not GetMonitorInfoW(monitor, reinterpret_cast<LPMONITORINFO>(&monitor_info)) )
    {
        return;
    }

    const RECT& work_area = monitor_info.rcWork;

    const int32_t work_area_width  = work_area.right - work_area.left;
    const int32_t work_area_height = work_area.bottom - work_area.top;

    const int32_t x = work_area.left + ((work_area_width - window_width) / 2);
    const int32_t y = work_area.top + ((work_area_height - window_height) / 2);

    SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}
