#pragma once

#include "Core/STL/String.hpp"

#include "Core/Platform/Windows/WinInclude.hpp"
#include "Core/Diagnostics/Assert.hpp"

#define WIN_OK(HRES_EXPR) SUCCEEDED(HRES_EXPR)
#define WIN_FAIL(HRES_EXPR) FAILED(HRES_EXPR)

#define WIN_CHECK(hResExpr)                                                       \
        do                                                                        \
        {                                                                         \
            [[maybe_unused]] HRESULT nfHr_ = hResExpr;                            \
            NF_ASSERT(WIN_OK(nfHr_), ::NF::OS::Windows::TranslateHResult(nfHr_)); \
        } while (false)


namespace NF::OS::Windows
{
    String TranslateHResult(HRESULT hRes);
}