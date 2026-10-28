#pragma once

#include <Private/D3D12/D3D12Include.hpp>
#include <Core/Diagnostics/Assert.hpp>

#include <Core/Types.hpp>
#include <Core/Utility/Helpers.hpp>

#include <Core/STL/Queue.hpp>
#include <Core/STL/HashSet.hpp>

namespace NF::RendererApi::D3D12
{
    class DescriptorHeap
    {
    public:

        NF_NOCOPY(DescriptorHeap);
        NF_NOMOVE(DescriptorHeap);
        
        DescriptorHeap() = default;

        void Create(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE desc_heap_type, u32 capacity);
        
        [[nodiscard]]
        u32 GetDescSize() const noexcept;
        [[nodiscard]]
        u32 GetIndex(D3D12_CPU_DESCRIPTOR_HANDLE handle) const;

        ID3D12DescriptorHeap* const GetHeapPtr()
        {
            NF_ASSERT(m_heap);
            return m_heap.Get();
        }

        operator ID3D12DescriptorHeap* const()
        {
            return GetHeapPtr();
        }

        ID3D12DescriptorHeap* const operator->()
        {
            return GetHeapPtr();
        }

        CD3DX12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(u32 index) const noexcept;
        CD3DX12_GPU_DESCRIPTOR_HANDLE GetGpuHandle(u32 index) const noexcept;

    protected:

        ComPtr<ID3D12DescriptorHeap> m_heap{};
        u32 m_descriptorSize{};
    };

    class CbvSrvUavHeap : public DescriptorHeap
    {
    public:

        CbvSrvUavHeap() = default;

        NF_NOCOPY(CbvSrvUavHeap);
        NF_NOMOVE(CbvSrvUavHeap);

        // todo: this looks like bad design, 2 initialize functions, i don't like it
        void Create(ID3D12Device* device, u32 capacity);

        u32 GetNextFreeIndex();
        void ReleaseIndex(u32 index);

    private:

        Queue<u32> m_freeIndices;

        // only for validation, this can be only debug 
        HashSet<u32> m_usedIndices;
    };
}
