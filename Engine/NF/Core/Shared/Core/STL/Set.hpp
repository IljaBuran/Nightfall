#pragma once

#if defined(NF_USE_STL)

    #include <set>

#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<
        class Key,
        class Compare = ::std::less<Key>,
        class Allocator = ::std::allocator<Key>
    >

    using Set = ::std::set<Key, Compare, Allocator>;

#else

    #error "No custom STL implementation yet"

#endif
}