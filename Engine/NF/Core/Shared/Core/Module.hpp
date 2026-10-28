#pragma once

#include <Core/Utility/Helpers.hpp>
#include <Core/Configuration.hpp>

namespace NF { class Application; }

#define NF_MODULE(x)                         \
    friend class ::NF::Application;          \
    NF_NOCOPY(x);                            \
    NF_NOMOVE(x);                            \
    static void Init(Configuration& config); \
    static void BeginFrame();                \
    static void PreUpdate();                 \
    static void FixedUpdate();               \
    static void Update();                    \
    static void PostUpdate();                \
    static void Render();                    \
    static void EndFrame();                  \
    static void Shutdown()          
