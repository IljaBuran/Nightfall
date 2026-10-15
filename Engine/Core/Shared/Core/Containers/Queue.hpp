#pragma once

#if defined(NF_USE_STL)
#include <queue>

template<
    class T,
    class Container = std::deque<T>
>
using Queue = std::queue<T, Container>;
#endif // defined(NF_USE_STL)