#include "Private/pch.hpp"

#include "Module.hpp"

#include "Private/WinConsole.hpp"

namespace NF::Module
{
    void LogSink_WinConsole::Init()
    {
        NF::Logging::AddSink(
            MakeUnique<::NF::Logging::WinConsole>()
        );
    }

    void LogSink_WinConsole::BeginFrame()
    {
    }

    void LogSink_WinConsole::PreUpdate()
    {
    }

    void LogSink_WinConsole::FixedUpdate()
    {
    }

    void LogSink_WinConsole::Update()
    {
    }

    void LogSink_WinConsole::PostUpdate()
    {
    }

    void LogSink_WinConsole::Render()
    {
    }

    void LogSink_WinConsole::EndFrame()
    {
    }

    void LogSink_WinConsole::Shutdown()
    {
    }
}
