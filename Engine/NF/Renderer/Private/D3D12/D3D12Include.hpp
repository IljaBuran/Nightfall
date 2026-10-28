#pragma once

#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <d3d12.h>
#include <d3dx12.h>

#include <Core/Platform/Windows/WinUtil.hpp>


#pragma comment(lib, "dxgi.lib")

namespace NF::RendererApi::D3D12
{
    // DXGI
    using IDXGIFactoryVer   = IDXGIFactory6;
    using IDXGIAdapterVer   = IDXGIAdapter4;
    using IDXGISwapChainVer = IDXGISwapChain4;

    // D3D12
    using ID3D12DeviceVer              = ID3D12Device10;
    using ID3D12DebugVer               = ID3D12Debug3;
    using ID3D12FenceVer               = ID3D12Fence;
    using ID3D12CommandQueueVer        = ID3D12CommandQueue;
    using ID3D12GraphicsCommandListVer = ID3D12GraphicsCommandList7;
    using ID3D12CommandAllocatorVer    = ID3D12CommandAllocator;
    using ID3D12InfoQueueVer           = ID3D12InfoQueue1;

    static constexpr D3D_FEATURE_LEVEL D3D12_REQUIRED_FEATURE_LEVEL{ D3D_FEATURE_LEVEL_12_2 };
}