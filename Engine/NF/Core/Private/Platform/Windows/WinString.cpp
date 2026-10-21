#include "Private/pch.hpp"

#include "Shared/Core/Platform/Windows/WinString.hpp"

namespace NF::Windows
{
    WString Utf8ToWide(StringView str)
    {
        if (str.empty())
        {
            return WString{};
        }

        const INT required = MultiByteToWideChar(
            CP_UTF8,
            0,
            str.data(),
            static_cast<int>(str.size()),
            nullptr,
            0
        );

        if (required == 0)
        {
            // TODO(ilja): this is bad idea to let this fail silently...
        
            return WString{};
        }

        WString result;
        result.resize(required);

        const INT converted = MultiByteToWideChar(
            CP_UTF8,
            0,
            str.data(),
            static_cast<int>(str.size()),
            result.data(),
            required
        );

        if (converted == 0)
        {
            return WString{};
        }

        return result;
    }

    String WideToUtf8(WStringView str)
    {
        if (str.empty())
        {
            return String{};
        }

        const INT required = WideCharToMultiByte(
            CP_UTF8,
            0,
            str.data(),
            static_cast<int>(str.size()),
            nullptr,
            0,
            nullptr,
            nullptr
        );

        if (required == 0)
        {
            return String{};
        }

        String result;
        result.resize(required);

        const INT converted = WideCharToMultiByte(
            CP_UTF8,
            0,
            str.data(),
            static_cast<int>(str.size()),
            result.data(),
            required,
            nullptr,
            nullptr
        );

        if (converted == 0)
        {
            return String{};
        }

        return result;
    }
}
