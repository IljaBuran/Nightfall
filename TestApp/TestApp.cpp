#include <Application/Application.hpp>

#include <Core/Core.hpp>
#include <WinConsole/WinConsole.hpp>
#include <VSConsole/VSConsole.hpp>
#include <Window/Window.hpp>
#include <Renderer/Renderer.hpp>
#include <Core/Configuration.hpp>

#include <Core/Diagnostics/Debugging.hpp>
#include <Core/Diagnostics/Assert.hpp>
#include <Core/Logging/Logging.hpp>

int NF::Application::Main()
{
    ::NF::Configuration config
    {
        .windowHandle{ nullptr },
        .name{ "Nightfall Window" },
        .width{ 1920 },
        .height{ 1080 },

        // renderer
        .cbvSrvUavCapacity{ 64 },
        .framebufferCount{ 2 },
        .framesInFlight{ 3 },
        .vsync{ true },
    };
    
    auto assertHandle = []([[maybe_unused]] const ::NF::Diagnostics::AssertInfo& info) -> bool
    {
        return true;
    };

    ::NF::Diagnostics::SetAssertHandler(assertHandle);

    ::NF::Core::Init(config);
    ::NF::WinConsole::Init(config);
    ::NF::VSConsole::Init(config);
    ::NF::Window::Init(config);
    ::NF::Renderer::Init(config);

    while (!Window::ShouldClose())
    {
        ::NF::Core::BeginFrame();
        ::NF::WinConsole::BeginFrame();
        ::NF::VSConsole::BeginFrame();
        ::NF::Window::BeginFrame();
        ::NF::Renderer::BeginFrame();

        ::NF::Core::PreUpdate();
        ::NF::WinConsole::PreUpdate();
        ::NF::VSConsole::PreUpdate();
        ::NF::Window::PreUpdate();
        ::NF::Renderer::PreUpdate();

        ::NF::Core::FixedUpdate();
        ::NF::WinConsole::FixedUpdate();
        ::NF::VSConsole::FixedUpdate();
        ::NF::Window::FixedUpdate();
        ::NF::Renderer::FixedUpdate();

        ::NF::Core::Update();
        ::NF::WinConsole::Update();
        ::NF::VSConsole::Update();
        ::NF::Window::Update();
        ::NF::Renderer::Update();

        ::NF::Core::PostUpdate();
        ::NF::WinConsole::PostUpdate();
        ::NF::VSConsole::PostUpdate();
        ::NF::Window::PostUpdate();
        ::NF::Renderer::PostUpdate();

        ::NF::Core::Render();
        ::NF::WinConsole::Render();
        ::NF::VSConsole::Render();
        ::NF::Window::Render();
        ::NF::Renderer::Render();

        ::NF::Core::EndFrame();
        ::NF::WinConsole::EndFrame();
        ::NF::VSConsole::EndFrame();
        ::NF::Window::EndFrame();
        ::NF::Renderer::EndFrame();
    }

    ::NF::Renderer::Shutdown();
    ::NF::Window::Shutdown();
    ::NF::VSConsole::Shutdown();
    ::NF::WinConsole::Shutdown();
    ::NF::Core::Shutdown();

    return 0;
}