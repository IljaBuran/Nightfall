#include "pch.hpp"

#include "Logging/LogInternal.hpp"

#include "Core/Core.hpp"

namespace NF
{
    void Core::Init()
    {
        Log::RegisterDefaultSinks();
    }

    void Core::BeginFrame()
    {
    }

    void Core::PreUpdate()
    {
    }

    void Core::Update()
    {
    }

    void Core::PostUpdate()
    {
    }

    void Core::EndFrame()
    {
    }

    void Core::Shutdown()
    {
        Log::Shutdown();
    }
}