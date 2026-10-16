#pragma once

#include "Core/String.hpp"

namespace NF::Platform::Windows
{
    WString Utf8ToWide(StringView str);
    String WideToUtf8(WStringView str);
}
