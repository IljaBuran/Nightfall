#include "Private/pch.hpp"

#include "Core/Diagnostics/Debugging.hpp"

namespace NF::Diagnostics
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