#pragma once

#include "Shared/Core/STL/Array.hpp"
#include "Shared/Core/Types.hpp"

#include "Shared/Core/Diagnostics/Assert.hpp"

// TODO(ilja): this needs further functionaly, i'll implement it later (maybe hehe)
namespace NF
{
    template<typename T, u32 size>
    class RingBuffer
    {
    public:

        T& Add(T&& element) noexcept
        {
            T& slot = m_data[m_writeIndex];
            slot = std::move(element);

            m_writeIndex = (m_writeIndex + 1) % size;
            if (m_count < size) ++m_count;

            return slot;
        }
    
        [[nodiscard]]
        T& operator[](u32 index) noexcept
        {
            NF_ASSERT(index < m_count);

            const u32 oldest{ m_count == size ? m_writeIndex : 0 };

            return m_data[(static_cast<u64>(oldest) + index) % size];
        }

        [[nodiscard]]
        const T& operator[](u32 index) const noexcept
        {
            NF_ASSERT(index < m_count);

            const u32 oldest{ m_count == size ? m_writeIndex : 0 };

            return m_data[(static_cast<u64>(oldest) + index) % size];
        }

        [[nodiscard]]
        u32 Size() const noexcept
        {
            return m_count;
        }

    private:

        Array<T, size> m_data;
        u32 m_writeIndex{};
        u32 m_count{};
    };
}
