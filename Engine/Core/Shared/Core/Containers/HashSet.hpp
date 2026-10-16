#pragma once

#if defined(NF_USE_STL)

    #include <unordered_set>

#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<
        class Key,
        class Hash = ::std::hash<Key>,
        class KeyEqual = ::std::equal_to<Key>,
        class Allocator = ::std::allocator<Key>
    >
    using HashSet = ::std::unordered_set<Key, Hash, KeyEqual, Allocator>;

#else

    #error "No custom STL implementation yet"

#endif
}