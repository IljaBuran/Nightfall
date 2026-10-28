#pragma once

#if defined(NF_USE_STL)

#include <span>
#include <Core/Types.hpp>

#endif

namespace NF
{

#if defined(NF_USE_STL)

    template<
        class T,
        usize Extent = std::dynamic_extent
    >
    using Span = ::std::span<T, Extent>;

#else

#error "No custom STL implementation yet"

#endif
}