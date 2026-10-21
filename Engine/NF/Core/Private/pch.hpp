// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

/*---     Platform/compiler specific        ---*/
#include "Shared/Core/Platform/Platform.hpp"
#include "Shared/Core/Platform/Compiler.hpp"


/*---     Engine stl, containers, types, ...    ---*/
#include "Shared/Core/Types.hpp"

#include "Shared/Core/STL/Array.hpp"
#include "Shared/Core/STL/Format.hpp"
#include "Shared/Core/STL/Memory.hpp"
#include "Shared/Core/STL/String.hpp"
#include "Shared/Core/STL/Vector.hpp"


#if NF_WINDOWS

    #include "Shared/Core/Platform/Windows/WinInclude.hpp"
    #include "Shared/Core/Platform/Windows/WinDebug.hpp"

#endif // NF_WINDOWS

/*---     Engine parts     ---*/
#include "Shared/Core/Diagnostics/Assert.hpp"
#include "Shared/Core/Diagnostics/Debugging.hpp"
#include "Shared/Core/Logging/Logging.hpp"

#endif //PCH_H
