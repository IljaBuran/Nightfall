#include "pch.hpp"

#include "Core/Logging/ISink.hpp"
#include "Logging/LogInternal.hpp"

#include "Core/Assert.hpp"
#include "Core/Utility/Helpers.hpp"

#include "Core/Platform/Windows/WindowsString.hpp"


namespace NF::Platform::Windows
{
    namespace
    {
        constexpr WORD DefaultAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

        WORD AttributesForLevel(Log::Level level)
        {
            switch (level)
            {
                case Log::Level::Info:    return DefaultAttributes | FOREGROUND_INTENSITY;                  // white
                case Log::Level::Warning: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;  // yellow
                case Log::Level::Error:   return FOREGROUND_RED | FOREGROUND_INTENSITY;                     // red
                case Log::Level::Fatal:   return BACKGROUND_RED | DefaultAttributes | FOREGROUND_INTENSITY; // white on red
                case Log::Level::Count:   break;
            }
            return DefaultAttributes;
        }
        
        class ConsoleSink final : public ::NF::Log::ISink
        {
        public:
            
            NF_NOCOPY(ConsoleSink);
            NF_NOMOVE(ConsoleSink);

            ConsoleSink()
            {
                if (!GetConsoleWindow())
                {
                    m_ownsConsole = AllocConsole();
                }

                NF_VERIFY(SetConsoleTitleW(L"Nightfall Log [Native Windows Console]"));

                m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
                NF_ASSERT(m_consoleHandle && m_consoleHandle != INVALID_HANDLE_VALUE);

                if (HMENU menu{ GetSystemMenu(GetConsoleWindow(), FALSE) })
                    EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
            }

            ~ConsoleSink()
            {
                if (m_ownsConsole)
                    NF_VERIFY(FreeConsole());

                m_consoleHandle = nullptr;
            }

            void Write(const Log::Record& record) override
            {
                DWORD written{ 0 };
                WString converted{ Utf8ToWide(record.text) };
                converted += L"\n";

                SetConsoleTextAttribute(
                    m_consoleHandle,
                    AttributesForLevel(record.level)
                );

                WriteConsoleW(m_consoleHandle, converted.data(), static_cast<DWORD>(converted.size()), &written, nullptr);

                SetConsoleTextAttribute(
                    m_consoleHandle,
                    DefaultAttributes
                );
            }

        private:

            HANDLE m_consoleHandle{};
            BOOL m_ownsConsole{ false };
        };

        class DebuggerSink final : public Log::ISink
        {
        public:

            DebuggerSink() = default;

            ~DebuggerSink() = default;

            void Write(const Log::Record& record) override
            {
                WString converted{ Utf8ToWide(record.text) };
                converted += L'\n';
                OutputDebugStringW(converted.data());
            }
        };
    }
}

namespace NF::Log
{
    void RegisterDefaultSinks()
    {
        AddSink(MakeUnique<NF::Platform::Windows::ConsoleSink>());

        if (IsDebuggerPresent())
        {
            AddSink(MakeUnique<NF::Platform::Windows::DebuggerSink>());
        }
    }
}
