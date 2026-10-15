#pragma once

#include "Core/Types.hpp"
#include "Core/String.hpp"

#include <iterator>

namespace NF::Debug
{
    struct AssertInfo
    {
        const char* expression;
        const char* fileName;
        i32         line;
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