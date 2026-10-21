#pragma once

#include "Core/Platform/Compiler.hpp"
#include "Core/Diagnostics/Debugging.hpp"

#if defined(_DEBUG)

    #define NF_ASSERT(expr)                                                         \
            do                                                                      \
            {                                                                       \
                if (!(expr)) [[unlikely]]                                           \
                {                                                                   \
                    if (::NF::Diagnostics::Assert::OnAssertFailed({ #expr, __FILE__, __LINE__ })) \
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