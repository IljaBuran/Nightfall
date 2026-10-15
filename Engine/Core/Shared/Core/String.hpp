#pragma once

#if defined(NF_USE_STL)
#include <string>
#include <format>
namespace NF
{
    using String = std::string;
    using StringView = std::string_view;

    using WideString = std::wstring;
    using WideStringView = std::wstring_view;
}

#endif