#pragma once

#include <Core/Types.hpp>

#include <Core/STL/Array.hpp>
#include <Core/STL/String.hpp>
#include <Core/STL/Vector.hpp>

#include <bit>
#include <utility>

namespace NF
{
    enum class ShaderType : u8
    {
        VERTEX   = 1u,
        HULL     = 1u << 1,
        DOMAIN_  = 1u << 2,
        GEOMETRY = 1u << 3,
        PIXEL    = 1u << 4,
        COMPUTE  = 1u << 5,

        AMPLIFICATION = 1u << 6,
        MESH          = 1u << 7,
    };

    [[nodiscard]] constexpr
    ShaderType operator|(ShaderType lhs, ShaderType rhs)
    {
        return static_cast<ShaderType>(static_cast<u8>(lhs) | static_cast<u8>(rhs));
    }

    [[nodiscard]] constexpr
    ShaderType operator&(ShaderType lhs, ShaderType rhs)
    {
        return static_cast<ShaderType>(std::to_underlying(lhs) & std::to_underlying(rhs));
    }

    [[nodiscard]] constexpr
    u32 ShaderTypeToIndex(ShaderType type) noexcept
    {
        return std::countr_zero(std::to_underlying(type));
    }

    [[nodiscard]] constexpr
    StringView GetEntryPoint(ShaderType type)
    {
        switch (type)
        {
            case ShaderType::VERTEX:        return "VSMain";
            case ShaderType::HULL:          return "HSMain";
            case ShaderType::DOMAIN_:       return "DSMain";
            case ShaderType::GEOMETRY:      return "GSMain";
            case ShaderType::PIXEL:         return "PSMain";
            case ShaderType::COMPUTE:       return "CSMain";
            case ShaderType::AMPLIFICATION: return "ASMain";
            case ShaderType::MESH:          return "MSMain";
        }
        std::unreachable();
    }

    [[nodiscard]] constexpr
    StringView GetProfile(ShaderType type)
    {
        switch (type)
        {
            case ShaderType::VERTEX:        return "vs_6_6";
            case ShaderType::HULL:          return "hs_6_6";
            case ShaderType::DOMAIN_:       return "ds_6_6";
            case ShaderType::GEOMETRY:      return "gs_6_6";
            case ShaderType::PIXEL:         return "ps_6_6";
            case ShaderType::COMPUTE:       return "cs_6_6";
            case ShaderType::AMPLIFICATION: return "as_6_6";
            case ShaderType::MESH:          return "ms_6_6";
        }
        std::unreachable();
    }

    struct Shader
    {
        Array<Vector<byte>, 8> blobs;
        ShaderType             type{};
    };
}