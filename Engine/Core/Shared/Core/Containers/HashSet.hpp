#pragma once

#if defined(NF_USE_STL)
#include <unordered_set>

template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
using HashSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

#endif // defined(NF_USE_STL)