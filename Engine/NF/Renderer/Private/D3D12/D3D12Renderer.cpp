#include "Private/pch.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/Settings.hpp"

#include "Private/D3D12/Factory.hpp"
#include "Private/D3D12/Device.hpp"
#include "Private/D3D12/InfoQueue.hpp"
#include "Private/D3D12/CommandQueue.hpp"
#include "Private/D3D12/CommandList.hpp"
#include "Private/D3D12/DescriptorUtil.hpp"
#include "Private/D3D12/Swapchain.hpp"
#include "Private/D3D12/Fence.hpp"
#include "Private/D3D12/FrameResource.hpp"

#include <Core/STL/Array.hpp>

#pragma comment(lib, "d3d12.lib")

namespace NF
{
    namespace
    {
        using namespace RendererApi;

        RendererSettings settings;

        D3D12::Device device;
        D3D12::InfoQueue infoQueue;
        D3D12::CommandQueue commandQueue;
        D3D12::CommandList commandList;
        D3D12::CbvSrvUavHeap cbvSrvUavHeap;
        D3D12::DescriptorHeap dsvHeap;

        D3D12::SwapChain swapchain;

        D3D12::Fence fence;
        u64 frameNumber{ 0 };

        inline constexpr u32 MAX_FRAMES_IN_FLIGHT{ 3 };
        Array<D3D12::FrameResource, MAX_FRAMES_IN_FLIGHT> frameResources;
        D3D12::FrameResource* currFrameRes{ nullptr };

        D3D12_VIEWPORT viewport;
        D3D12_RECT     scissorRect;

        Array<float, 4> clearColor{ 0.0f, 0.0f, 0.0f, 1.0f };

        void FlushEverything();
    }

    void Renderer::Init(Configuration& config)
    {
        NF_ASSERT(config.width && config.height && config.windowHandle &&
            config.cbvSrvUavCapacity && config.framebufferCount && 
            config.framesInFlight && config.framesInFlight <= MAX_FRAMES_IN_FLIGHT,
            "These need to be valid here!");

        settings.framebufferCount = config.framebufferCount;
        settings.framesInFlight = config.framesInFlight;
        settings.vsync = config.vsync;

        ::NF::RendererApi::D3D12::Factory factory;

        device.Create(factory);
    #ifdef D3D_DEBUG
        infoQueue.Initialize(device);
    #endif

        commandQueue.Create(device, D3D12_COMMAND_LIST_TYPE_DIRECT);

        cbvSrvUavHeap.Create(device, config.cbvSrvUavCapacity);

        dsvHeap.Create(device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1);

        swapchain.Create(factory, device, commandQueue,
            static_cast<HWND>(config.windowHandle), config.width, config.height, config.framebufferCount);

        for (u32 i{ 0 }; i < settings.framesInFlight; ++i)
        {
            frameResources[i].Create(device);
        }

        commandList.Create(device, D3D12_COMMAND_LIST_TYPE_DIRECT, frameResources[0].m_commandAllocator, nullptr);
        
        WIN_CHECK(commandList->Close());

        fence.Create(device);
    }

    void Renderer::BeginFrame()
    {
        currFrameRes = &frameResources[frameNumber % settings.framesInFlight];
        
        fence.Wait(currFrameRes->m_fenceValue);
        
        WIN_CHECK(currFrameRes->m_commandAllocator->Reset());
        WIN_CHECK(commandList->Reset(currFrameRes->m_commandAllocator, nullptr));
    }

    void Renderer::PreUpdate()
    {
    }

    void Renderer::FixedUpdate()
    {
    }

    void Renderer::Update()
    {
        const f32 t = frameNumber * 0.002f;
        clearColor[0] = 0.1f + 0.5f * std::sin(t);
        clearColor[1] = 0.1f + 0.5f * std::sin(t + 2.094f);
        clearColor[2] = 0.1f + 0.5f * std::sin(t + 4.189f);
    }

    void Renderer::PostUpdate()
    {
    }

    void Renderer::Render()
    {
        UINT backbufferIndex{ swapchain->GetCurrentBackBufferIndex() };
        auto& backbuffer{ swapchain.m_buffers[backbufferIndex] };
        auto rtvHandle{ swapchain.m_rtvHeap.GetCpuHandle(backbufferIndex) };

        D3D12_RESOURCE_BARRIER resourceBarrier
        {
            CD3DX12_RESOURCE_BARRIER::Transition(
                backbuffer.Get(),
                D3D12_RESOURCE_STATE_PRESENT,
                D3D12_RESOURCE_STATE_RENDER_TARGET)
        };
        commandList->ResourceBarrier(1, &resourceBarrier);
        commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

        commandList->ClearRenderTargetView(rtvHandle, clearColor.data(), 0, nullptr);

        resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
                backbuffer.Get(),
                D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATE_PRESENT
        );
        commandList->ResourceBarrier(1, &resourceBarrier);
    }

    void Renderer::EndFrame()
    {
        WIN_CHECK(commandList->Close());

        const Array<ID3D12CommandList*, 1> listsToExecute{ commandList };
        commandQueue->ExecuteCommandLists((UINT)listsToExecute.size(), listsToExecute.data());

        WIN_CHECK(swapchain->Present(
            settings.vsync ? 1 : 0, 
            0
        ));

        currFrameRes->m_fenceValue = fence.Signal(commandQueue);
        ++frameNumber;
    }

    void Renderer::Shutdown()
    {
        FlushEverything();

        infoQueue.Destroy();
    }

    namespace
    {
        using namespace RendererApi;

        void FlushEverything()
        {
            u64 value{ fence.Signal(commandQueue) };
            fence.Wait(value);
        }
    }
}
