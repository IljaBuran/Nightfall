#include <NF/NightfallConfig.hpp>
#include <Application/Application.hpp>

#include <NF/Core/Module.hpp>
#include <NF/LogSink.WinConsole/Module.hpp>
#include <NF/LogSink.VSDebug/Module.hpp>
//#include <NF/Window/Module.hpp>
//#include <NF/Input/Module.hpp>
//#include <NF/Renderer/Module.hpp>

#include <Core/Diagnostics/Debugging.hpp>
#include <Core/Logging/Logging.hpp>

int NF::Application::Main()
{
    ::NF::Module::Core::Init();
    ::NF::Module::LogSink_WinConsole::Init();
    ::NF::Module::LogSink_VSDebug::Init();
    //::NF::Window::Init();
    //::NF::Input::Init();
    //::NF::Renderer::Init();

    i32 i{ 0 };

    while (true)
    {
        ::NF::Module::Core::BeginFrame();
        ::NF::Module::LogSink_WinConsole::BeginFrame();
        ::NF::Module::LogSink_VSDebug::BeginFrame();

        ::NF::Module::Core::PreUpdate();
        ::NF::Module::LogSink_WinConsole::PreUpdate();
        ::NF::Module::LogSink_VSDebug::PreUpdate();

        ::NF::Module::Core::FixedUpdate();
        ::NF::Module::LogSink_WinConsole::FixedUpdate();
        ::NF::Module::LogSink_VSDebug::FixedUpdate();

        ::NF::Module::Core::Update();
        ::NF::Module::LogSink_WinConsole::Update();
        ::NF::Module::LogSink_VSDebug::Update();

        ::NF::Module::Core::PostUpdate();
        ::NF::Module::LogSink_WinConsole::PostUpdate();
        ::NF::Module::LogSink_VSDebug::PostUpdate();

        ::NF::Module::Core::Render();
        ::NF::Module::LogSink_WinConsole::Render();
        ::NF::Module::LogSink_VSDebug::Render();

        ::NF::Module::Core::EndFrame();
        ::NF::Module::LogSink_WinConsole::EndFrame();
        ::NF::Module::LogSink_VSDebug::EndFrame();

        NF_LOG_INFO("i: {}", i++);

        if (i == 100)
        {
            NF_LOG_ERROR("i==100");
            NF_DEBUGBREAK();
        }
    }

    ::NF::Module::LogSink_VSDebug::Shutdown();
    ::NF::Module::LogSink_WinConsole::Shutdown();
    ::NF::Module::Core::Shutdown();

    return 0;
}