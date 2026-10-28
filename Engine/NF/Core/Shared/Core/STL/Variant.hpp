#pragma once

#if defined(NF_USE_STL)

#include <variant>

#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<class... Types>
    using Variant = ::std::variant<Types...>;

#else

#error "No custom STL implementation yet"

#endif
}