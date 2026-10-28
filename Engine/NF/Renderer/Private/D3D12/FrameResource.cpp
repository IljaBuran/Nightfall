#include "Private/pch.hpp"

#include "Private/D3D12/FrameResource.hpp"

namespace NF::RendererApi::D3D12
{
    void FrameResource::Create(ID3D12DeviceVer* device)
    {
        m_commandAllocator.Create(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
        //m_passCB.Create(device, passCount, true);
    }

    FrameResource::~FrameResource() {}
}
