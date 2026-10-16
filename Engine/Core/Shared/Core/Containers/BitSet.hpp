#pragma once

#include <bit>

#include "Core/Assert.hpp"
#include "Core/Types.hpp"
#include "Core/Containers/Array.hpp"

namespace NF
{
    template<usize N>
    class BitSet
    {
        static_assert(N > 0, "BitSet must have at least one bit");

    public:

        static constexpr usize BitCount{ N };
        static constexpr usize WordBits{ 64 };
        static constexpr usize WordCount{ (N + WordBits - 1) / WordBits };
        static constexpr usize InvalidIndex{ static_cast<usize>(-1) };

        constexpr 
        BitSet() = default;

        constexpr
        void Set1(usize index)
        {
            NF_ASSERT(index < N);

            m_words[index / WordBits] |= BitMask(index);
        }

        constexpr 
        void Set0(usize index)
        {
            NF_ASSERT(index < N);

            m_words[index / WordBits] &= ~BitMask(index);
        }

        constexpr 
        void Flip(usize index)
        {
            NF_ASSERT(index < N);

            m_words[index / WordBits] ^= BitMask(index);
        }

        [[nodiscard]] constexpr
        bool Test(usize index) const
        {
            NF_ASSERT(index < N);

            return (m_words[index / WordBits] & BitMask(index)) != 0;
        }

        constexpr
        void Set1All() noexcept
        {
            for (u64& word : m_words)
            {
                word = ~u64{ 0 };
            }
            ClearUnusedBits();
        }
     
        constexpr
        void Set0All() noexcept
        {
            for (u64& word : m_words)
            {
                word = 0;
            }
        }
     
        [[nodiscard]] constexpr
        usize CountOf1s() const noexcept
        {
            usize count{};
            
            for (const auto word : m_words)
            {
                count += static_cast<usize>(std::popcount(word));
            }

            return count;
        }

        [[nodiscard]] constexpr
        bool Any() const noexcept
        {
            for (const auto word : m_words)
            {
                if (word != 0)
                {
                    return true;
                }
            }

            return false;
        }

        [[nodiscard]] constexpr
        bool None() const noexcept
        {
            return !Any();
        }

        [[nodiscard]] constexpr
        bool All() const noexcept
        {
            return CountOf1s() == N;
        }

        [[nodiscard]] constexpr
        usize FindFirstSet() const noexcept
        {
            for (usize i = 0; i < WordCount; ++i)
            {
                if (m_words[i] != 0)
                {
                    return i * WordBits + static_cast<usize>(std::countr_zero(m_words[i]));
                }
            }
            return InvalidIndex;
        }

        [[nodiscard]] constexpr
        usize FindFirstUnset() const noexcept
        {
            for (usize i = 0; i < WordCount; ++i)
            {
                if (m_words[i] != ~u64{0})
                {
                    const usize index{ i * WordBits + static_cast<usize>(std::countr_one(m_words[i])) };
                    return index >= N ? InvalidIndex : index;
                }
            }
            return InvalidIndex;
        }

        constexpr 
        BitSet& operator&=(const BitSet& other)
        {
            for (usize i = 0; i < WordCount; ++i)
            {
                m_words[i] &= other.m_words[i];
            }
            return *this;
        }

        constexpr 
        BitSet& operator|=(const BitSet& other)
        {
            for (usize i = 0; i < WordCount; ++i)
            {
                m_words[i] |= other.m_words[i];
            }
            return *this;
        }

        constexpr 
        BitSet& operator^=(const BitSet& other)
        {
            for (usize i = 0; i < WordCount; ++i)
            {
                m_words[i] ^= other.m_words[i];
            }
            return *this;
        }

        [[nodiscard]] constexpr 
        BitSet operator~() const
        {
            BitSet result;
            for (usize i = 0; i < WordCount; ++i)
            {
                result.m_words[i] = ~m_words[i];
            }
            result.ClearUnusedBits();
            return result;
        }

        [[nodiscard]] friend constexpr 
        BitSet operator&(BitSet a, const BitSet& b) 
        { 
            a &= b; 
            return a; 
        }

        [[nodiscard]] friend constexpr 
        BitSet operator|(BitSet a, const BitSet& b) 
        { 
            a |= b; 
            return a;
        }

        [[nodiscard]] friend constexpr 
        BitSet operator^(BitSet a, const BitSet& b) 
        { 
            a ^= b; 
            return a; 
        }

        [[nodiscard]] constexpr bool operator==(const BitSet&) const = default;

        [[nodiscard]] constexpr
        const Array<u64, WordCount>& GetRawData() const noexcept
        {
            return m_words;
        }

    private: // methods

        static constexpr
        u64 BitMask(u64 index)
        {
            return u64{ 1 } << (index % WordBits);
        }

        static constexpr u64 LastWordMask{ (N % WordBits == 0) ? ~u64{ 0 } : ((u64{ 1 } << (N % WordBits)) - 1) };

        constexpr
        void ClearUnusedBits() noexcept
        {
            m_words[WordCount - 1] &= LastWordMask;
        }

    private: // variables 

        Array<u64, WordCount> m_words{};
    };
}