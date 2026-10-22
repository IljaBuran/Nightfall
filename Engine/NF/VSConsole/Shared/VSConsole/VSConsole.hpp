#pragma once

#include <Core/Module.hpp>

#include <Core/Utility/Helpers.hpp>
#include <Core/Logging/ISink.hpp>

namespace NF
{
    class VSConsole final : public ::NF::Logging::ISink
    {
        NF_MODULE(VSConsole); // keep this in private

        VSConsole();

    public:
        
        ~VSConsole();

        void Write(const ::NF::Logging::Record& record) override;
    };
}
