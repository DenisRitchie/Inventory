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

export module Inventory:Win32;

export namespace Inventory::Win32
{
    struct CommandLineArgs
    {
        int32_t                  Argc { };
        std::vector<std::string> Storage;
        std::vector<char*>       Argv;
    };

    std::string     WCharToUtf8(const std::wstring_view text) noexcept;
    CommandLineArgs GetCommandLineArguments() noexcept;

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

Inventory::Win32::CommandLineArgs Inventory::Win32::GetCommandLineArguments() noexcept
{
    CommandLineArgs result { };

    int32_t wide_argc = 0;
    LPWSTR* wide_argv = CommandLineToArgvW(GetCommandLineW(), &wide_argc);

    if ( wide_argv == nullptr || wide_argc <= 0 )
    {
        return result;
    }

    result.Storage.reserve(wide_argc);
    result.Argv.reserve(wide_argc);

    for ( int32_t i = 0; i < wide_argc; ++i )
    {
        auto& arg = result.Storage.emplace_back(WCharToUtf8(wide_argv[i]));
        result.Argv.push_back(arg.data());
    }

    result.Argc = static_cast<int32_t>(result.Argv.size());

    LocalFree(wide_argv);
    return result;
}
