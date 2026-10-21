#include <Application/Application.hpp>

#include <Core/Core.hpp>
#include <WinConsole/WinConsole.hpp>
#include <VSConsole/VSConsole.hpp>
#include <Window/Window.hpp>

#include <Core/Diagnostics/Debugging.hpp>
#include <Core/Logging/Logging.hpp>

int NF::Application::Main()
{
    const ::NF::Window::Config config
    {
        .name{"Nightfall Window"},
        .width{},
        .height{}
    };
    
    ::NF::Core::Init();
    ::NF::WinConsole::Init();
    ::NF::VSConsole::Init();
    ::NF::Window::Init(config);

    while (!Window::ShouldClose())
    {
        ::NF::Core::BeginFrame();
        ::NF::WinConsole::BeginFrame();
        ::NF::VSConsole::BeginFrame();
        ::NF::Window::BeginFrame();

        ::NF::Core::PreUpdate();
        ::NF::WinConsole::PreUpdate();
        ::NF::VSConsole::PreUpdate();
        ::NF::Window::PreUpdate();

        ::NF::Core::FixedUpdate();
        ::NF::WinConsole::FixedUpdate();
        ::NF::VSConsole::FixedUpdate();
        ::NF::Window::FixedUpdate();

        ::NF::Core::Update();
        ::NF::WinConsole::Update();
        ::NF::VSConsole::Update();
        ::NF::Window::Update();

        ::NF::Core::PostUpdate();
        ::NF::WinConsole::PostUpdate();
        ::NF::VSConsole::PostUpdate();
        ::NF::Window::PostUpdate();

        ::NF::Core::Render();
        ::NF::WinConsole::Render();
        ::NF::VSConsole::Render();
        ::NF::Window::Render();

        ::NF::Core::EndFrame();
        ::NF::WinConsole::EndFrame();
        ::NF::VSConsole::EndFrame();
        ::NF::Window::EndFrame();
    }

    ::NF::Window::Shutdown();
    ::NF::VSConsole::Shutdown();
    ::NF::WinConsole::Shutdown();
    ::NF::Core::Shutdown();

    return 0;
}