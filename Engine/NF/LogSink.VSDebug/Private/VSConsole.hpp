#pragma once

#include <Core/Utility/Helpers.hpp>
#include <Core/Logging/ISink.hpp>

namespace NF::Logging
{
    class VSConsole final : public ::NF::Logging::ISink
    {
    public:

        NF_NOCOPY(VSConsole);
        NF_NOMOVE(VSConsole);

        void Write(const ::NF::Logging::Record& record) override;
    };
}
