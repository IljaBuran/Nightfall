// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H


/*---     Engine stl, containers, types, ...    ---*/
#include "Core/String.hpp"
#include "Core/Types.hpp"
#include "Core/Containers/Array.hpp"
#include "Core/Containers/Vector.hpp"

/*---     Engine stl, containers, types, ...    ---*/
#include <format>


/*---     Platform/compiler specific        ---*/
#include "Core/Platform/PlatformDetection.hpp"
#include "Core/Platform/CompilerDetection.hpp"

#if NF_WINDOWS

    #include "Core/Platform/Windows/WindowsPlatform.hpp"
    #include "Core/Platform/Windows/WindowsDebug.hpp"

#endif // NF_WINDOWS

/*---     Engine parts     ---*/
#include "Core/Assert.hpp"
#include "Core/Debug.hpp"

#endif //PCH_H
