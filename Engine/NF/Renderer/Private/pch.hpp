// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <Core/Platform/Platform.hpp>

#include <Core/Diagnostics/Assert.hpp>

#if defined(NF_WINDOWS)

    #if defined(_DEBUG)
        #define D3D_DEBUG
    #endif 

    #include <Core/Platform/Windows/WinInclude.hpp>
    #include <Core/Platform/Windows/WinDebug.hpp>
    #include <Core/Platform/Windows/WinString.hpp>
    #include <Core/Platform/Windows/WinUtil.hpp>

    #include <Private/D3D12/D3D12Include.hpp>

    #include <DirectXShaderCompiler/inc/dxcapi.h>

#endif

#include <Core/Types.hpp>
#include <Core/Logging/Logging.hpp>

#include <Core/STL/Array.hpp>
#include <Core/STL/Optional.hpp>
#include <Core/STL/String.hpp>
#include <Core/STL/Vector.hpp>

#endif //PCH_H
