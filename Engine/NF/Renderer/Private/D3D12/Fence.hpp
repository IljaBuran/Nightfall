#pragma once

#include "Private/D3D12/D3D12Include.hpp"

#include <Core/Platform/Windows/WinDebug.hpp>
#include <Core/Diagnostics/Assert.hpp>
#include <Core/Types.hpp>
#include <Core/Utility/Helpers.hpp>

namespace NF::RendererApi::D3D12
{
    class Fence
    {
    public:

        NF_NOCOPY(Fence);
        NF_NOMOVE(Fence);

        Fence() = default;

        void Create(ID3D12DeviceVer* device);

        u64 Signal(ID3D12CommandQueueVer* commandQueue)
        {
            WIN_CHECK(commandQueue->Signal(m_d3d12Fence.Get(), ++m_counter));
            return m_counter;
        }

        void Wait(u64 value) noexcept
        {
            if (m_d3d12Fence->GetCompletedValue() < value)
            {
                WIN_CHECK(m_d3d12Fence->SetEventOnCompletion(value, m_fenceEvent.Get()));
                NF_VERIFY(WaitForSingleObject(m_fenceEvent.Get(), INFINITE) == WAIT_OBJECT_0);
            }
        }

        [[nodiscard]]
        ID3D12FenceVer* GetFencePtr()
        {
            NF_ASSERT(m_d3d12Fence);
            return m_d3d12Fence.Get();
        }

        [[nodiscard]]
        ID3D12FenceVer* operator->()
        {
            return GetFencePtr();
        }

        [[nodiscard]]
        operator ID3D12FenceVer* ()
        {
            return GetFencePtr();
        }

    private:

        ComPtr<ID3D12FenceVer> m_d3d12Fence;
        WinEvent m_fenceEvent;
        u64 m_counter{ 0 };
    };
}
