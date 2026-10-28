#pragma once

#include "Private/D3D12/D3D12Include.hpp"
#include "Private/D3D12/DescriptorUtil.hpp"

#include <Core/Platform/Windows/WinDebug.hpp>
#include <Core/Math/BasicMath.hpp>


namespace NF::RendererApi::D3D12
{
    template<typename T>
    class UploadBuffer
    {
    public:

        UploadBuffer() = default;

        ~UploadBuffer()
        {
            if (m_uploadBuffer)
            {
                m_uploadBuffer->Unmap(0, nullptr);
            }
            m_mappedData = nullptr;
        }

        void Create(ID3D12DeviceVer* device, u64 elementCount, bool isConstantBuffer)
        {
            m_elementCount = elementCount;
            m_elementByteSize = sizeof(T);

            if (isConstantBuffer)
            {
                m_elementByteSize = 
                    static_cast<u32>(Math::AlignUp(m_elementByteSize, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT));
            }

            auto properties{ CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD) };
            auto description{ CD3DX12_RESOURCE_DESC::Buffer(m_elementByteSize * elementCount) };

            WIN_CHECK(device->CreateCommittedResource(
                &properties,
                D3D12_HEAP_FLAG_NONE,
                &description,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&m_uploadBuffer)
            ));

            auto range{ CD3DX12_RANGE(0, 0) };
            WIN_CHECK(m_uploadBuffer->Map(0, &range, reinterpret_cast<void**>(&m_mappedData)));
        }
        
        void CopyData(i32 elementIndex, const T& data)
        {
            NF_ASSERT(m_uploadBuffer);
            NF_ASSERT(elementIndex < m_elementCount);

            std::memcpy(
                &m_mappedData[elementIndex * m_elementByteSize],
                &data,
                sizeof(T)
            );
        }

        void CopyData(const T* data, u32 count)
        {
            NF_ASSERT(m_uploadBuffer);
            NF_ASSERT(m_elementByteSize == sizeof(T));
            NF_ASSERT(count < m_elementCount);

            std::memcpy(
                m_mappedData,
                data,
                static_cast<size_t>(count) * m_elementByteSize
            );
        }

        ID3D12Resource* GetResourcePtr()
        {
            NF_ASSERT(m_uploadBuffer);
            return m_uploadBuffer.Get();
        }

        u32 GetElementByteSize() const noexcept
        {
            NF_ASSERT(m_uploadBuffer);
            return m_elementByteSize;
        }

        UploadBuffer(const UploadBuffer&) = delete;
        UploadBuffer(UploadBuffer&&) = delete;
        void operator=(const UploadBuffer&) = delete;
        void operator=(UploadBuffer&&) = delete;

    private:

        ComPtr<ID3D12Resource> m_uploadBuffer;
        byte* m_mappedData{ nullptr };

        u64 m_elementCount{ 0 };
        u32 m_elementByteSize{ 0 };
        bool m_isConstantBuffer{ false };
    };
}