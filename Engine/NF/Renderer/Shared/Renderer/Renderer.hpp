#pragma once

#include <Core/Module.hpp>
#include <Core/Configuration.hpp>

namespace NF
{
    class Renderer
    {
        NF_MODULE(Renderer); // this should stay private

    public: // your implementation

        template<typename Tag>
        struct Handle
        {
            static constexpr u32 INDEX_BITS = 20;
            static constexpr u32 INDEX_MASK = (1u << INDEX_BITS) - 1;

            u32 value;

            [[nodiscard]] u32  Index()      const { return value & INDEX_MASK; }
            [[nodiscard]] u32  Generation() const { return value >> INDEX_BITS; }
            [[nodiscard]] bool IsValid()    const { return value != 0; }
        };


        using MeshHandle = Handle<struct MeshTag>;
        using MaterialHandle = Handle<struct MaterialTag>;
    };
}
