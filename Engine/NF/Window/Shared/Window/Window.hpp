#pragma once

#include <Core/Module.hpp>
#include <Core/Types.hpp>

#include <Core/STL/Pair.hpp>
#include <Core/STL/String.hpp>

namespace NF
{
    class Window
    {
        NF_MODULE(Window); // this should stay private

        struct Config
        {
            void*      handle{}; // e.g. win32 HWND from Editor
            StringView name{};
            u32        width{};
            u32        height{};
        };

        static
        void Init(const Config& config);

    public: 

        [[nodiscard]] static
        Pair<u32, u32> GetWindowSize() noexcept;

        [[nodiscard]] static
        bool IsMinimized() noexcept;

        [[nodiscard]] static
        bool IsFocused() noexcept;

        [[nodiscard]] static 
        bool IsFullscreen() noexcept;

        [[nodiscard]] static 
        bool ShouldClose() noexcept;

        [[nodiscard]] static
        void* GetNativeWindowHandle() noexcept;
    };
}
