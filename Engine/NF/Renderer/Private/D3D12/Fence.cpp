#include "Private/pch.hpp"
#include "Fence.hpp"

namespace NF::RendererApi::D3D12
{
    void Fence::Create(ID3D12DeviceVer* device)
    {
        m_counter = 0;
        WIN_CHECK(device->CreateFence(
            0, 
            D3D12_FENCE_FLAG_NONE, 
            IID_PPV_ARGS(&m_d3d12Fence)
        ));

        m_fenceEvent.Attach(
            CreateEvent(nullptr, false, false, nullptr)
        );

        NF_ASSERT(m_fenceEvent.IsValid());
    }
}