#pragma once

#if defined(NF_USE_STL)

    #include <unordered_map>

#endif

namespace NF
{
#if defined(NF_USE_STL)

	template<
		typename Key,
		typename T,
		typename Hash = ::std::hash<Key>,
		typename KeyEqual = ::std::equal_to<Key>,
		typename Allocator = ::std::allocator<::std::pair<const Key, T>>
	>

	using HashMap = ::std::unordered_map<
		Key,
		T,
		Hash,
		KeyEqual,
		Allocator
	>;

#else

    #error "No custom STL implementation yet"

#endif
}