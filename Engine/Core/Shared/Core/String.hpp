#pragma once

#if defined(NF_USE_STL)

    #include <string>

#endif

namespace NF
{
#if defined(NF_USE_STL)

    using String     = ::std::string;
    using StringView = ::std::string_view;

    using WString     = ::std::wstring;
    using WStringView = ::std::wstring_view;

#else

    #error "No custom STL implementation yet"

#endif
}