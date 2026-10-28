#pragma once

#include <Core/Types.hpp>

namespace NF
{
    struct RendererSettings
    {
        u8   framebufferCount{};
        u8   framesInFlight{};
        bool vsync{};
    };
}