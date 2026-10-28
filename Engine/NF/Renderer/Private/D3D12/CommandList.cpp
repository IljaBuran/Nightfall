#include "Private/pch.hpp"

#include "Private/D3D12/CommandList.hpp"

namespace NF::RendererApi::D3D12
{
    void CommandList::Create(
        ID3D12DeviceVer* device, 
        D3D12_COMMAND_LIST_TYPE type, 
        ID3D12CommandAllocatorVer* allocator, 
        ID3D12PipelineState* initialState
    )
    {
        NF_ASSERT(device && allocator);
        
        WIN_CHECK(device->CreateCommandList(
            0 /* FOR SINGLE ADAPTER PROGRAMS IT'S OK TO SET THIS TO 0 */,
            type,
            allocator,
            initialState,
            IID_PPV_ARGS(&m_d3d12CommandList)
        ));
    }
}