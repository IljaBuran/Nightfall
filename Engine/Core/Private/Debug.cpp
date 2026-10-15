#include "pch.hpp"

#include "Core/Debug.hpp"

namespace NF::Debug
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