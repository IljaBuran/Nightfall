// this file is AI-generated (Claude, claude-opus-5-5): 
// Prompt: "can you make std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared and std::weak_ptr according to other containers I made aliases for?"

#pragma once

#include <memory>

namespace NF
{
    template<typename T, typename Deleter = ::std::default_delete<T>>
    using UniquePtr = ::std::unique_ptr<T, Deleter>;

    template<typename T, typename... Args>
    [[nodiscard]] inline UniquePtr<T> MakeUnique(Args&&... args)
    {
        return ::std::make_unique<T>(::std::forward<Args>(args)...);
    }

#if defined(NF_USE_STL)

    template<typename T>
    using SharedPtr = ::std::shared_ptr<T>;

    template<typename T>
    using WeakPtr = ::std::weak_ptr<T>;


    template<typename T, typename... Args>
    [[nodiscard]] inline SharedPtr<T> MakeShared(Args&&... args)
    {
        return ::std::make_shared<T>(::std::forward<Args>(args)...);
    }

#else

    #error "No custom STL implementation yet"

#endif
}