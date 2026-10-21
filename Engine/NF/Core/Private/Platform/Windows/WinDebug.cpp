#include "Private/pch.hpp"

#include "Shared/Core/Platform/Windows/WinString.hpp"

#include "Shared/Core/Types.hpp"

namespace NF::Diagnostics::Debugging::Windows
{
    String TranslateHResult(HRESULT hr)
    {
        wchar_t* buffer = nullptr;
        const DWORD length = FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, static_cast<DWORD>(hr), 0, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);

        if (length == 0)
            return std::format("Unknown error 0x{:08X}", static_cast<u32>(hr));

        String result = ::NF::Windows::WideToUtf8({ buffer, length });
        LocalFree(buffer);

        while (!result.empty() && (result.back() == '\n' || result.back() == '\r'))
            result.pop_back();
        return result;
    }
}