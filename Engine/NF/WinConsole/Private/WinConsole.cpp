#include <Private/pch.hpp>

#include <WinConsole/WinConsole.hpp>

namespace NF
{
    namespace
    {
        constexpr WORD DefaultAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        HANDLE m_consoleHandle{};
        BOOL m_ownsConsole{ false };

        WORD AttributesForLevel(::NF::Logging::Level level);
    }

    void WinConsole::Init([[maybe_unused]] Configuration& config)
    {
        ::NF::Logging::AddSink(UniquePtr<WinConsole>(new WinConsole()));
    }

    void WinConsole::BeginFrame()
    {
    }

    void WinConsole::PreUpdate()
    {
    }

    void WinConsole::FixedUpdate()
    {
    }

    void WinConsole::Update()
    {
    }

    void WinConsole::PostUpdate()
    {
    }

    void WinConsole::Render()
    {
    }

    void WinConsole::EndFrame()
    {
    }

    void WinConsole::Shutdown()
    {
    }


    WinConsole::WinConsole()
    {
        if (!GetConsoleWindow())
        {
            m_ownsConsole = AllocConsole();
        }

        NF_VERIFY(SetConsoleTitleW(L"Nightfall Log [Native Windows Console]"));

        m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        NF_ASSERT(m_consoleHandle && m_consoleHandle != INVALID_HANDLE_VALUE);

        if (HMENU menu{ GetSystemMenu(GetConsoleWindow(), FALSE) })
        {
            EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
        }
    }

    WinConsole::~WinConsole()
    {
        if (m_ownsConsole)
        {
            NF_VERIFY(FreeConsole());
        }

        m_consoleHandle = nullptr;
    }

    void WinConsole::Write(const ::NF::Logging::Record& record)
    {
        DWORD written{ 0 };
        WString converted{ ::NF::OS::Windows::Utf8ToWide(record.text) };
        converted += L"\n";

        SetConsoleTextAttribute(
            m_consoleHandle,
            AttributesForLevel(record.level)
        );

        WriteConsoleW(
            m_consoleHandle, 
            converted.data(), 
            static_cast<DWORD>(converted.size()), 
            &written, 
            nullptr
        );

        SetConsoleTextAttribute(
            m_consoleHandle,
            DefaultAttributes
        );
    }

    namespace
    {
        WORD AttributesForLevel(::NF::Logging::Level level)
        {
            switch (level)
            {
                case ::NF::Logging::Level::Info:    return DefaultAttributes | FOREGROUND_INTENSITY;                  // white
                case ::NF::Logging::Level::Warning: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;  // yellow
                case ::NF::Logging::Level::Error:   return FOREGROUND_RED | FOREGROUND_INTENSITY;                     // red
                case ::NF::Logging::Level::Fatal:   return BACKGROUND_RED | DefaultAttributes | FOREGROUND_INTENSITY; // white on red
                case ::NF::Logging::Level::Count:   break;
            }
            return DefaultAttributes;
        }
    }
}
