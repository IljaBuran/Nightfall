#pragma once

#if defined(NF_USE_STL)

    #include <vector>

#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<
        class T,
        class Allocator = ::std::allocator<T>
    >
    using Vector = ::std::vector<T, Allocator>;

#else

    #error "No custom STL implementation yet"

#endif
}