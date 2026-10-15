#pragma once

#include "Core/Types.hpp"

#if defined(NF_USE_STL)
#include <array>               // file scope
#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<typename T, usize N>
    using Array = ::std::array<T, N>;

#else

#error "NF::Array: own implementation not written yet"
    // later: template<typename T, usize N> class Array { ... };

#endif
}