#include "Private/pch.hpp"

#include "VSConsole/VSConsole.hpp"

namespace NF
{
    void VSConsole::Init()
    {
        ::NF::Logging::AddSink(MakeUnique<VSConsole>());
    }

    void VSConsole::BeginFrame()
    {
    }

    void VSConsole::PreUpdate()
    {
    }

    void VSConsole::FixedUpdate()
    {
    }

    void VSConsole::Update()
    {
    }

    void VSConsole::PostUpdate()
    {
    }

    void VSConsole::Render()
    {
    }

    void VSConsole::EndFrame()
    {
    }

    void VSConsole::Shutdown()
    {
    }

    VSConsole::VSConsole()
    {
    }

    VSConsole::~VSConsole()
    {
    }

    void VSConsole::Write(const ::NF::Logging::Record& record)
    {
        WString converted{ ::NF::Windows::Utf8ToWide(record.text) };
        converted += L'\n';
        OutputDebugStringW(converted.data());
    }
}
