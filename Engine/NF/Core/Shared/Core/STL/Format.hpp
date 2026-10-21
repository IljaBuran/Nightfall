#pragma once

#include "Core/STL/String.hpp"
#include "Core/Types.hpp"

#if defined(NF_USE_STL)

    #include <format>

#endif

namespace NF
{

#if defined(NF_USE_STL)

    template<typename... Args>
    using FormatString = ::std::format_string<Args...>;

    // Compile-time checked: Format("x = {}", x)
    template<typename... Args>
    [[nodiscard]] inline String Format(FormatString<Args...> fmt, Args&&... args)
    {
        return ::std::format(fmt, ::std::forward<Args>(args)...);
    }

    // Append into an existing buffer, no temporary String
    template<typename OutputIt, typename... Args>
    inline OutputIt FormatTo(OutputIt out, FormatString<Args...> fmt, Args&&... args)
    {
        return ::std::format_to(out, fmt, ::std::forward<Args>(args)...);
    }

    // Exact output length, e.g. to size a buffer up front
    template<typename... Args>
    [[nodiscard]] inline usize FormattedSize(FormatString<Args...> fmt, Args&&... args)
    {
        return static_cast<usize>(::std::formatted_size(fmt, ::std::forward<Args>(args)...));
    }

    // Runtime format string (config, files); throws std::format_error on a bad string
    template<typename... Args>
    [[nodiscard]] inline String FormatRuntime(StringView fmt, Args&... args)
    {
        return ::std::vformat(fmt, ::std::make_format_args(args...));
    }

#else

    #error "No custom STL implementation yet"

#endif
}