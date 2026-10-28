#pragma once

#include <Core/Types.hpp>

#include <Core/STL/String.hpp>

namespace NF
{
    struct Configuration
    {
        void*      windowHandle{};
        StringView name{};
        u32        width{};
        u32        height{};

        // renderer
        u32 cbvSrvUavCapacity{};
        u8 framebufferCount{};
        u8 framesInFlight{};
        bool vsync{};
    };
}
