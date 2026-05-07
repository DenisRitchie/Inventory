module;

#include "Framework.hpp"

export module Main;

import Inventory;

int32_t APIENTRY wWinMain(
    [[maybe_unused]] _In_ HINSTANCE     hInstance,       // Handle to the current instance of the application
    [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance,   // Handle to the previous instance of the application (not used in modern Windows applications)
    [[maybe_unused]] _In_ LPWSTR        lpCmdLine,       // Command line arguments as a Unicode string
    [[maybe_unused]] _In_ int32_t       nCmdShow         // Controls how the window is to be shown (e.g., SW_SHOW, SW_HIDE, etc.
)
{
    auto command_line_arguments = Inventory::Win32::GetCommandLineArguments();
    return Inventory::Main(command_line_arguments);
}
