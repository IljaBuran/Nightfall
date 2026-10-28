#pragma once

#include <Core/Types.hpp>

#include <Core/STL/String.hpp>
#include <Core/STL/Vector.hpp>

namespace NF::Utility
{
    struct DisplayDesc
    {
        struct DisplayMode
        {
            u32 width{};
            u32 height{};
            u32 refreshRate{};
        };
        
        String name{};
        u32    width{};
        u32    height{};
        u32    maxRefreshRate{};

        Vector<DisplayMode> supportedModes;
    };

    struct GpuDesc
    {
        String name{};
        f32 dedicatedMemoryInGBs{};
    };
}
