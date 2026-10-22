#include "Private/pch.hpp"

#include "Application/Application.hpp"

int WINAPI wWinMain(
    [[maybe_unused]] _In_     HINSTANCE hInstance, 
    [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, 
    [[maybe_unused]] _In_     LPWSTR pCmdLine, 
    [[maybe_unused]] _In_     int nCmdShow
)
{
    SetProcessDpiAwarenessContext(
        DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 // this restricts to post v1703 Windows 10 version 
    );

    return ::NF::Application::Main();
}