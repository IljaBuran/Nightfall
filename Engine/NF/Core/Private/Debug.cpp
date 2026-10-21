#include "Private/pch.hpp"

#include "Shared/Core/Diagnostics/Debugging.hpp"

namespace NF::Diagnostics::Assert
{
    static AssertHandler s_handler = nullptr;
    
    void SetAssertHandler(AssertHandler handler)
    {
        s_handler = handler;
    }

    bool OnAssertFailed(const AssertInfo& info)
    {
        return s_handler ? s_handler(info) : true;
    }
}