#pragma once

#if defined(NF_USE_STL)
#include <vector>

template<
    class T,
    class Allocator = std::allocator<T>
>
using Vector = std::vector<T, Allocator>;
#endif // defined(NF_USE_STL)