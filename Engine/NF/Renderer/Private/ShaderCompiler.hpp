#pragma once

#include "Private/Shader.hpp"
#include <Core/STL/Optional.hpp>
#include <Core/STL/Memory.hpp>

namespace NF
{ 
    class ShaderCompiler
    {

    public:

        ShaderCompiler();
        Optional<Shader> Compile(StringView path, ShaderType type) noexcept;
    };
};