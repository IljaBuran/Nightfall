#pragma once

#include "Core/Types.hpp"
#include "Core/STL/String.hpp"
#include "Core/STL/Format.hpp"

#define NF_LOG_INFO(...) ::NF::Logging::Info(__VA_ARGS__)
#define NF_LOG_WARNING(...) ::NF::Logging::Warning(__VA_ARGS__)
#define NF_LOG_ERROR(...) ::NF::Logging::Error(__VA_ARGS__)

namespace NF::Logging
{
    enum class Level : u8
    {
        Info,
        Warning,
        Error,
        Fatal,
        Count
    };

    // prerequisites: the message needs to be already formatted
    void Write(Level level, StringView message);

    template<typename... Args>
    void Info(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Info, ::NF::Format(fmt, ::std::forward<Args>(args)...));
    }

    template<typename... Args>
    void Warning(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Warning, ::NF::Format(fmt, ::std::forward<Args>(args)...));
    }

    template<typename... Args>
    void Error(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Error, ::NF::Format(fmt, ::std::forward<Args>(args)...));
    }

    template<typename... Args>
    void Fatal(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Fatal, ::NF::Format(fmt, ::std::forward<Args>(args)...));
    }
}
