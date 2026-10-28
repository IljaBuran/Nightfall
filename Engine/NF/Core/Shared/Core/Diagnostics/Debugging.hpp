#pragma once

#include "Core/Types.hpp"
#include "Core/STL/String.hpp"

#include "Core/Platform/Compiler.hpp"

#if defined(NF_MSVC)
    #define NF_DEBUGBREAK() __debugbreak()
#elif defined(NF_CLANG)
    #define NF_DEBUGBREAK() __builtin_debugtrap()
#elif defined(NF_GCC)
#include <signal.h>
    #define NF_DEBUGBREAK() raise(SIGTRAP)
#endif


namespace NF::Diagnostics
{
    struct AssertInfo
    {
        const char* expression;
        const char* fileName;
        i32         line;
        String      message{};
    };

    using AssertHandler = bool (*)(const AssertInfo&);

    void SetAssertHandler(AssertHandler handler);
    bool OnAssertFailed(const AssertInfo& info);
}
    
//class ILLException
//{
//public:
//        
//    ILLException() = delete;
//    explicit ILLException(HRESULT hRes, const String& functionName, const String& fileName, i32 lineNumber)
//        : m_hRes(hRes), m_functionName(functionName), m_fileName(fileName), m_lineNumber(lineNumber) {}
//
//    String GetErrorMessage() const
//    {
//        _com_error err(m_hRes);
//        String errMsg = TranslateHResult(m_hRes);
//
//        return std::format(L"File: {}\nLine: {}\nFunction: {}, HRESULT error code: {}, HRESULT error msg: {}",
//            m_fileName, m_lineNumber, m_functionName, static_cast<i32>(m_hRes), errMsg);
//    }
//
//private:
//        
//    HRESULT m_hRes;
//    String  m_functionName;
//    String  m_fileName;
//    i32     m_lineNumber;
//};