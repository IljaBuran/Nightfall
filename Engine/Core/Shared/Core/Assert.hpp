#pragma once

#include "Core/Platform/CompilerDetection.hpp"
#include "Core/Debug.hpp"

#if defined(_DEBUG)

    #define NF_ASSERT(expr)                                                         \
            do                                                                      \
            {                                                                       \
                if (!(expr)) [[unlikely]]                                           \
                {                                                                   \
                    if (::NF::Debug::OnAssertFailed({ #expr, __FILE__, __LINE__ })) \
                    {                                                               \
                        NF_DEBUGBREAK();                                            \
                    }                                                               \
                }                                                                   \
            } while (false)
    
    #define NF_VERIFY(expr) NF_ASSERT(expr)

#else

    #define NF_ASSERT(expr) ((void)0)
    #define NF_VERIFY(expr) ((void)(expr))

#endif