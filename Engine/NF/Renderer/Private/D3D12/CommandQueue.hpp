#pragma once

#include <Private/D3D12/D3D12Include.hpp>

#include <Core/Types.hpp>
#include <Core/Utility/Helpers.hpp>

namespace NF::RendererApi::D3D12
{
    class CommandQueue
    {
    public:

        NF_NOCOPY(CommandQueue);
        NF_NOMOVE(CommandQueue);
        
        CommandQueue() = default;

        void Create(
            ID3D12DeviceVer* device, 
            D3D12_COMMAND_LIST_TYPE type, 
            D3D12_COMMAND_QUEUE_PRIORITY priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
            D3D12_COMMAND_QUEUE_FLAGS flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
            u32 nodeMask = 0
        );

        ID3D12CommandQueue* GetCommandQueuePtr()
        {
            return m_d3d12CommandQueue.Get();
        }

        ID3D12CommandQueueVer* operator->()
        {
            return GetCommandQueuePtr();
        }

        operator ID3D12CommandQueueVer*()
        {
            return GetCommandQueuePtr();
        }

    private:

        ComPtr<ID3D12CommandQueueVer> m_d3d12CommandQueue;
    };


}


