#include "Private/pch.hpp"

#include "Application/Application.hpp"

int WINAPI wWinMain(
    [[maybe_unused]] _In_     HINSTANCE hInstance, 
    [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, 
    [[maybe_unused]] _In_     LPWSTR pCmdLine, 
    [[maybe_unused]] _In_     int nCmdShow
)
{
    return ::NF::Application::Main();
}