#pragma once

#include <Core/Module.hpp>

namespace NF::Module
{
    class LogSink_WinConsole
    {
        NF_MODULE(LogSink_WinConsole);

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
