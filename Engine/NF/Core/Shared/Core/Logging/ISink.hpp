#pragma once

#include "Core/STL/Memory.hpp"
#include "Core/STL/String.hpp"
#include "Core/Logging/Logging.hpp"

namespace NF::Logging
{
    struct Record
    {
        Level level{ Level::Count };
        String text;
    };

    class ISink
    {
    public:

        virtual ~ISink() = default;

        ISink() = default;

        // prerequisites: here it needs to receive already formatted string,
        //                the ISink is responsible for is coloring
        virtual void Write(const Record& record) = 0;
    };

    void AddSink(UniquePtr<ISink> sink);
}
