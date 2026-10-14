// Core : Nightfall Module
#pragma once

// This is standard interface your module will interact with engine
namespace NF
{
    class Core
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