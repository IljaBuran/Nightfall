#pragma once

#include <Private/D3D12/D3D12Include.hpp>

#include <Private/D3D12/DescriptorUtil.hpp>

#include <Core/Diagnostics/Assert.hpp>

#include <Core/Types.hpp>
#include <Core/Utility/Helpers.hpp>

#include <Core/STL/Vector.hpp>
#include <Core/STL/Pair.hpp>

namespace NF::RendererApi::D3D12
{
    class SwapChain
    {
    public:

        NF_NOCOPY(SwapChain);
        NF_NOMOVE(SwapChain);

        SwapChain() = default;

        void Create(
            IDXGIFactoryVer* factory,
            ID3D12DeviceVer* device,
            ID3D12CommandQueueVer* commandQueue, 
            HWND hWnd,
            u32 width, 
            u32 height,
            u8 framebufferCount
        );
        
        void Resize(ID3D12DeviceVer* device, i32 newWidth, i32 newHeight);
        
        Pair<u32, u32> GetSize() const
        {
            return Pair<u32, u32>{m_renderTargetWidth, m_renderTargetHeight};
        }
        
        f32 GetAspectRatio() const
        {
            return m_aspectRatio;
        }

        IDXGISwapChainVer* GetSwapChainPtr()
        {
            NF_ASSERT(m_dxgiSwapChain);

            return m_dxgiSwapChain.Get();
        }

        IDXGISwapChainVer* operator->()
        {
            return GetSwapChainPtr();
        }

        operator IDXGISwapChainVer*()
        {
            return GetSwapChainPtr();
        }

        Vector<ComPtr<ID3D12Resource>> m_buffers{};
        DescriptorHeap                 m_rtvHeap{};

    private:

        void _UpdateAspectRatio();

    private:

        ComPtr<IDXGISwapChainVer> m_dxgiSwapChain{};

        u32 m_renderTargetWidth{};
        u32 m_renderTargetHeight{};
        f32 m_aspectRatio{};
    };
}