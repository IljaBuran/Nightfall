#pragma once

#if defined(NF_USE_STL)

#include <utility>

template<typename T1, typename T2>
using Pair = std::pair<T1, T2>;

#endif // defined(NF_USE_STL)
