#pragma once

#include "Core/Log.hpp"
#include "Core/Memory/Memory.hpp"

#include "Core/Utility/Helpers.hpp"

namespace NF::Log
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
