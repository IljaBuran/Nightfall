#pragma once

#include <Core/Utility/Helpers.hpp>
#include <Core/Logging/ISink.hpp>

namespace NF::Logging
{
    class WinConsole final : public ::NF::Logging::ISink
    {
    public:

        NF_NOCOPY(WinConsole);
        NF_NOMOVE(WinConsole);

        WinConsole();

        ~WinConsole();

        void Write(const ::NF::Logging::Record& record) override;

    private:

        static constexpr WORD DefaultAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

        static WORD AttributesForLevel(::NF::Logging::Level level);

    private:

        HANDLE m_consoleHandle{};
        BOOL m_ownsConsole{ false };
    };
}
