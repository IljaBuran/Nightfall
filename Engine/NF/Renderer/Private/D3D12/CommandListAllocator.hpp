#pragma once

#include "Private/D3D12/D3D12Include.hpp"

#include <Core/Diagnostics/Assert.hpp>
#include <Core/Utility/Helpers.hpp>


namespace NF::RendererApi::D3D12
{
    class CommandListAllocator
    {
    public:

        NF_NOCOPY(CommandListAllocator);
        NF_NOMOVE(CommandListAllocator);

        CommandListAllocator() = default;

        void Create(ID3D12DeviceVer* const device, D3D12_COMMAND_LIST_TYPE type);

        ID3D12CommandAllocator* const GetAllocPtr()
        {
            NF_ASSERT(m_d3d12commandAllocator);

            return m_d3d12commandAllocator.Get();
        }

        ID3D12CommandAllocator* const operator->()
        {
            return GetAllocPtr();
        }

        operator ID3D12CommandAllocator* const()
        {
            return GetAllocPtr();
        }

    private:

        ComPtr<ID3D12CommandAllocator> m_d3d12commandAllocator;
    };
}