#pragma once

#if defined(NF_USE_STL)

#include <set>

template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>

using Set = std::set<Key, Compare, Allocator>;

#endif // defined(NF_USE_STL)