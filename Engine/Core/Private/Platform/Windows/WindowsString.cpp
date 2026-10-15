#include "pch.hpp"

#include "Core/Platform/Windows/WindowsString.hpp"

namespace NF::Platform::Windows
{
    WideString Utf8ToWide(StringView str)
    {
        if (str.empty())
        {
            return WideString{};
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
        
            return WideString{};
        }

        WideString result;
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
            return WideString{};
        }

        return result;
    }

    String WideToUtf8(WideStringView str)
    {
        if (str.empty())
        {
            return String{};
        }

        const int required = WideCharToMultiByte(
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

        const int converted = WideCharToMultiByte(
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
