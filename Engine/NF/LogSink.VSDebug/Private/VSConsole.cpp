#include "Private/pch.hpp"
#include "Private/VSConsole.hpp"

namespace NF::Logging
{
    void VSConsole::Write(const ::NF::Logging::Record& record)
    {
        WString converted{ ::NF::Windows::Utf8ToWide(record.text) };
        converted += L'\n';
        OutputDebugStringW(converted.data());
    }
}
