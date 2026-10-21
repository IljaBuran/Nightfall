#pragma once

#include "Shared/Core/Module.hpp"

namespace NF::Module
{
    class Core
    {
        NF_MODULE(Core);

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