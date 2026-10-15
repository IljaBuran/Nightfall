#pragma once

#if defined(NF_USE_STL)

#include <map>

template<
    typename Key,
    typename T,
    typename Compare   = std::less<Key>,
    typename Allocator = std::allocator<std::pair<const Key, T>>
>

using Map = std::map<Key, T, Compare, Allocator>;

#endif // defined(NF_USE_STL)
