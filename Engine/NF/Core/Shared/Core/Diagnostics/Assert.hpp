#pragma once

#include "Core/Platform/Compiler.hpp"
#include "Core/Diagnostics/Debugging.hpp"
#include "Core/Logging/Logging.hpp"

#if defined(_DEBUG)

    #define NF_ASSERT(expr, ...)                                            \
            do                                                              \
            {                                                               \
                if (!(expr)) [[unlikely]]                                   \
                {                                                           \
                    ::NF::Diagnostics::AssertInfo nfAssertInfo_             \
                    {                                                       \
                        .expression{ #expr },                               \
                        .fileName{ __FILE__ },                              \
                        .line{ __LINE__ },                                  \
                        .message{ __VA_ARGS__ }                             \
                    };                                                      \
                                                                            \
                    NF_LOG_ERROR("Assert failed.\n"                         \
                                 "File name: {}\n"                          \
                                 "Expression: {}\n"                         \
                                 "Line: {}"                                 \
                                 __VA_OPT__("\nMessage: {}"),               \
                        nfAssertInfo_.fileName, nfAssertInfo_.expression, nfAssertInfo_.line __VA_OPT__(, nfAssertInfo_.message)); \
                                                                            \
                    if (::NF::Diagnostics::OnAssertFailed(nfAssertInfo_))   \
                    {                                                       \
                        NF_DEBUGBREAK();                                    \
                    }                                                       \
                }                                                           \
            } while (false)
    
    #define NF_VERIFY(expr) NF_ASSERT(expr)

#else

    #define NF_ASSERT(expr, ...) ((void)0)
    #define NF_VERIFY(expr, ...) ((void)(expr))

#endif