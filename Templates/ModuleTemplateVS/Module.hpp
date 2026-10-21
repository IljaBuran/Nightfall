#pragma once

#include <Core/Module.hpp>

namespace NF::Module
{
    class $safeprojectname$
    {
        NF_MODULE($safeprojectname$);

    private:

        static void Init();
        static void BeginFrame();
        static void PreUpdate();
        static void FixedUpdate();
        static void Update();
        static void PostUpdate();
        static void Render();
        static void EndFrame();
        static void Shutdown();

    };
}
