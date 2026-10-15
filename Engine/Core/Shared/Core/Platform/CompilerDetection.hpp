#pragma once

#if defined(_MSC_VER)

#define NF_MSVC 1
#define NF_DEBUGBREAK() __debugbreak()
#define NF_FORCEINLINE __forceinline

#elif defined(__clang__)

#define NF_CLANG 1
#define NF_DEBUGBREAK() __builtin_debugtrap()
#define NF_FORCEINLINE inline __attribute__((always_inline))

#elif defined(__GNUC__)

#define NF_GCC 1
#define NF_DEBUGBREAK() __builtin_trap()
#define NF_FORCEINLINE inline __attribute__((always_inline))

#else

#error "Unsupported compiler"

#endif // _MSC_VER