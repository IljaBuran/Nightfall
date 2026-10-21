// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here

#include <Core/Platform/Platform.hpp>

#if defined(NF_WINDOWS)

    #include <Core/Platform/Windows/WinInclude.hpp>
    #include <Core/Platform/Windows/WinDebug.hpp>    
    #include <Core/Platform/Windows/WinString.hpp>    

#endif

#include <Core/Types.hpp>

#include <Core/Diagnostics/Assert.hpp>

#include <Core/Logging/Logging.hpp>
#endif //PCH_H
