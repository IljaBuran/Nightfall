#pragma once

#include "Core/String.hpp"

namespace NF::Platform::Windows
{
    WideString Utf8ToWide(StringView str);
    String WideToUtf8(WideStringView str);
}
