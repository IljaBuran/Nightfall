#pragma once

#define WIN_OK(HRES_EXPR) SUCCEEDED(HRES_EXPR)
#define WIN_FAIL(HRES_EXPR) FAILED(HRES_EXPR)
#define WIN_CHECK(x)                                                          \
{												                              \
    HRESULT __hRes = x;							                              \
    if (FAILED(__hRes))							                              \
    {										                                  \
        __debugbreak();                                                       \
        String __fileNameW(__FILEW__);		                                  \
        throw ILLException(__hRes, String(L#x), String(__FILEW__), __LINE__); \
    }                                                                         \
}