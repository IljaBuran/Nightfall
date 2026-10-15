#pragma once

#if defined(NF_USE_STL)
#include <bitset>

template <std::uint64_t size>
using BitSet = std::bitset<size>;
#endif