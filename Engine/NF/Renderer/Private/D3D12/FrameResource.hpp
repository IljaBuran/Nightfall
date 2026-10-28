#pragma once

#include "Private/D3D12/D3D12Include.hpp"
#include "Private/D3D12/CommandListAllocator.hpp"
#include "Private/D3D12/UploadBuffer.hpp"

#include <Core/Types.hpp>
#include <Core/Utility/Helpers.hpp>

namespace NF::RendererApi::D3D12
{
    class FrameResource
    {
    public:

        NF_NOCOPY(FrameResource);
        NF_NOMOVE(FrameResource);

        FrameResource() = default;

        void Create(ID3D12DeviceVer* device);
        ~FrameResource();

        CommandListAllocator m_commandAllocator;
        //D3D12::UploadBuffer<PassConstants> m_passCB;
        u64 m_fenceValue{};
    };
}
