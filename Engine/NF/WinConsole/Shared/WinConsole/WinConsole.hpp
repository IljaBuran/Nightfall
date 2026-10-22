#pragma once

#include <Core/Module.hpp>
#include <Core/Logging/ISink.hpp>

namespace NF
{
    class WinConsole final : public ::NF::Logging::ISink
    {
        NF_MODULE(WinConsole); // this should to stay in private

        WinConsole();

    public:
        
        ~WinConsole();

        void Write(const ::NF::Logging::Record& record) override;
    };
}