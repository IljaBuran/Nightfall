#include <Private/pch.hpp>
#include <Private/D3D12/DescriptorUtil.hpp>


namespace NF::RendererApi::D3D12
{
    void DescriptorHeap::Create(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE descHeapType, u32 capacity)
    {
        NF_ASSERT(!m_heap);
        NF_ASSERT(device);

        D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc
        {
            .Type = descHeapType,
            .NumDescriptors = capacity,
            .Flags = (descHeapType == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV || descHeapType == D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER) ?
            D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
            .NodeMask = 0
        };

        WIN_CHECK(device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_heap.GetAddressOf())));

        m_descriptorSize = device->GetDescriptorHandleIncrementSize(descHeapType);
    }

    u32 DescriptorHeap::GetDescSize() const noexcept
    {
        NF_ASSERT(m_heap);

        return m_descriptorSize;
    }

    u32 DescriptorHeap::GetIndex(D3D12_CPU_DESCRIPTOR_HANDLE handle) const
    {
        NF_ASSERT(m_heap);

        const D3D12_CPU_DESCRIPTOR_HANDLE start{m_heap->GetCPUDescriptorHandleForHeapStart()};

        NF_ASSERT(handle.ptr >= start.ptr);

        return static_cast<u32>((handle.ptr - start.ptr) / m_descriptorSize);
    }

    CD3DX12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCpuHandle(u32 index) const noexcept
    {
        NF_ASSERT(m_heap);

        CD3DX12_CPU_DESCRIPTOR_HANDLE hCpu(m_heap->GetCPUDescriptorHandleForHeapStart());
        hCpu.Offset(index, m_descriptorSize);
        return hCpu;
    }

    CD3DX12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGpuHandle(u32 index) const noexcept
    {
        NF_ASSERT(m_heap);
        CD3DX12_GPU_DESCRIPTOR_HANDLE hGpu(m_heap->GetGPUDescriptorHandleForHeapStart());

        hGpu.Offset(index, m_descriptorSize);
        return hGpu;
    }

    void CbvSrvUavHeap::Create(ID3D12Device* device, u32 capacity)
    {
        NF_ASSERT(device && capacity > 0);
        DescriptorHeap::Create(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, capacity);

        for (u32 i = 0; i < capacity; ++i)
            m_freeIndices.push(i);

        m_usedIndices.clear();
    }

    u32 CbvSrvUavHeap::GetNextFreeIndex()
    {
        NF_ASSERT(m_heap);
        NF_ASSERT(!m_freeIndices.empty());

        const i32 index = m_freeIndices.front();

        m_usedIndices.insert(index);

        m_freeIndices.pop();
        return index;
    }

    void CbvSrvUavHeap::ReleaseIndex(u32 index)
    {
        NF_ASSERT(m_heap);
        auto it = m_usedIndices.find(index);
        NF_ASSERT(it != m_usedIndices.end());

        m_usedIndices.erase(it);
        m_freeIndices.push(index);
    }
}
