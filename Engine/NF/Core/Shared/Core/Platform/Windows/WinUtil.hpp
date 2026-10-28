#pragma once

#include <wrl/client.h>
#include <wrl/wrappers/corewrappers.h>

namespace NF
{
    // WRL - Windows specific wrappers
    template<typename T>
    using ComPtr = ::Microsoft::WRL::ComPtr<T>;
    using WinEvent = ::Microsoft::WRL::Wrappers::Event;
}