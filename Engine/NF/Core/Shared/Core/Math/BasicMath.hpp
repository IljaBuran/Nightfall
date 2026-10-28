#pragma once

#include <Core/Platform/Compiler.hpp>
#include <Core/Diagnostics/Assert.hpp>
#include <Core/Constants.hpp>

namespace NF::Math
{
    template<typename T>
    concept HasLessComparator = requires(T t)
    {
        { t < t } -> std::convertible_to<bool>;
    };

    [[nodiscard]] NF_FORCEINLINE constexpr
    bool IsPowerOf2(std::uint64_t value) noexcept
    {
        return (value & (value - 1)) == 0;
    }

    [[nodiscard]] NF_FORCEINLINE constexpr
    std::uint64_t AlignUp(std::uint64_t value, std::uint64_t alignment) noexcept
    {
        NF_ASSERT(alignment != 0 && IsPowerOf2(alignment));
        const std::uint64_t mask = alignment - 1;
        NF_ASSERT(value <= U64_MAX - mask);
        return (value + mask) & ~mask;
    }

    template<HasLessComparator T>
    [[nodiscard]] NF_FORCEINLINE constexpr
    T Clamp(const T& value, const T& min, const T& max)
    {
        assert(min < max);

        if (value < min)
            return min;
        if (max < value)
            return max;
        return value;
    }
}
