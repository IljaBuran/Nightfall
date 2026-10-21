#pragma once

#include "Shared/Core/Types.hpp"

#include <array>

namespace NF
{
    template<typename T, size_t N>
    using Array = ::std::array<T, N>;
}