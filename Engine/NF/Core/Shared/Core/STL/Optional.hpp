#pragma once

#if defined(NF_USE_STL)

#include <optional>
#include <type_traits>
#include <utility>


#endif

namespace NF
{
#if defined(NF_USE_STL)

    template<class T>
    using Optional = std::optional<T>;

    template<class T>
    constexpr Optional<std::decay_t<T>> MakeOptional(T&& value)
    {
        return std::make_optional(std::forward<T>(value));
    }

    template<class T, class... Args>
    constexpr Optional<T> MakeOptional(Args&&... args)
    {
        return std::make_optional<T>(std::forward<Args>(args)...);
    }

#else

#error "No custom STL implementation yet"

#endif
}