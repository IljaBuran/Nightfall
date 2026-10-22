#pragma once

#include "Core/STL/String.hpp"

namespace NF::OS::Windows
{
    WString Utf8ToWide(StringView str);
    String WideToUtf8(WStringView str);
}
