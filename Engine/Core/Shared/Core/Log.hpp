#pragma once

#include "Core/Types.hpp"
#include "Core/String.hpp"

#include <format>

#define NF_LOG_INFO(...) ::NF::Log::Info(__VA_ARGS__)
#define NF_LOG_WARNING(...) ::NF::Log::Warning(__VA_ARGS__)
#define NF_LOG_ERROR(...) ::NF::Log::Error(__VA_ARGS__)

namespace NF::Log
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
        Write(Level::Info, ::std::format(fmt, ::std::forward<Args>(args)...));
    }

    template<typename... Args>
    void Warning(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Warning, ::std::format(fmt, ::std::forward<Args>(args)...));
    }

    template<typename... Args>
    void Error(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Error, ::std::format(fmt, ::std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    void Fatal(::std::format_string<Args...> fmt, Args&&... args)
    {
        Write(Level::Fatal, ::std::format(fmt, ::std::forward<Args>(args)...));
    }

}
