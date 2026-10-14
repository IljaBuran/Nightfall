// $safeprojectname$ : Nightfall Module

#pragma once

#include <Core/Core.hpp>

// This is standard interface your module will interact with engine
namespace NF
{
    class $safeprojectname$
    {
    public:

        void Init();
        void BeginFrame();
        void PreUpdate();
        void Update();
        void PostUpdate();
        void EndFrame();
        void Shutdown();

    };
}
