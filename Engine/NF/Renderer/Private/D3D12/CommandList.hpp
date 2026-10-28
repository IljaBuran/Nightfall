#pragma once

#include <Private/D3D12/D3D12Include.hpp>

#include <Core/Diagnostics/Assert.hpp>
#include <Core/Utility/Helpers.hpp>

namespace NF::RendererApi::D3D12
{
    class CommandList
    {
    public:

        NF_NOCOPY(CommandList);
        NF_NOMOVE(CommandList);

        CommandList() = default;

        void Create(
            ID3D12DeviceVer* device, 
            D3D12_COMMAND_LIST_TYPE type, 
            ID3D12CommandAllocator* allocator, 
            ID3D12PipelineState* initialState = nullptr
        );

        ID3D12GraphicsCommandListVer* GetCommandListPtr()
        {
            NF_ASSERT(m_d3d12CommandList);
            return m_d3d12CommandList.Get();
        }

        ID3D12GraphicsCommandListVer* operator->()
        {
            return GetCommandListPtr();
        }

        operator ID3D12GraphicsCommandListVer*()
        {
            return GetCommandListPtr();
        }

    private:

        ComPtr<ID3D12GraphicsCommandListVer> m_d3d12CommandList;
    };
}