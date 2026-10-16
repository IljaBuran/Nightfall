#pragma once

#if defined(NF_USE_STL)

    #include <queue>

#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<
        class T,
        class Container = ::std::deque<T>
    >
    using Queue = ::std::queue<T, Container>;

#else

    #error "No custom STL implementation yet"

#endif
}