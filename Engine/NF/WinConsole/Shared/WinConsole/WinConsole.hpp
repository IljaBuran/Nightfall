#pragma once

#include <Core/Module.hpp>
#include <Core/Logging/ISink.hpp>

#include <Core/Platform/Windows/WinInclude.hpp>

namespace NF
{
    class WinConsole final : public ::NF::Logging::ISink
    {
        NF_MODULE(WinConsole); // this should to stay in private

    public:

        WinConsole();
        ~WinConsole();
      
        void Write(const ::NF::Logging::Record& record) override;

    private:

        static constexpr WORD DefaultAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

        static WORD AttributesForLevel(::NF::Logging::Level level);

    private:

        inline static HANDLE m_consoleHandle{};
        inline static BOOL m_ownsConsole{ false };
    };

}