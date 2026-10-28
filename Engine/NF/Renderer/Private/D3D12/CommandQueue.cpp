#include "Private/pch.hpp"

#include "Private/D3D12/CommandQueue.hpp"

namespace NF::RendererApi::D3D12
{
    void CommandQueue::Create(
        ID3D12DeviceVer* const device, 
        D3D12_COMMAND_LIST_TYPE type, 
        D3D12_COMMAND_QUEUE_PRIORITY priority, 
        D3D12_COMMAND_QUEUE_FLAGS flags, 
        u32 nodeMask
    )
    {
        D3D12_COMMAND_QUEUE_DESC queueDesc
        {
            .Type{type},
            .Priority{priority},
            .Flags{flags},
            .NodeMask{nodeMask}
        };

        WIN_CHECK(device->CreateCommandQueue(
            &queueDesc,
            IID_PPV_ARGS(&m_d3d12CommandQueue)
        ));
    }
}