#include <Private/pch.hpp>

#include "Private/D3D12/Device.hpp"
#include "Private/D3D12/Helpers.hpp"

namespace NF::RendererApi::D3D12
{
    void Device::Create(IDXGIFactoryVer* factory)
    {
    #if defined(D3D_DEBUG)

        ComPtr<ID3D12DebugVer> debugController;
        WIN_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));

        debugController->EnableDebugLayer();
        debugController->SetEnableGPUBasedValidation(true);

    #endif
        
        HRESULT hRes{};
        for (u32 i{ 0 }; WIN_OK(factory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&m_dxgiAdapter))); ++i)
        {
            hRes = D3D12CreateDevice(m_dxgiAdapter.Get(), D3D12_REQUIRED_FEATURE_LEVEL, IID_PPV_ARGS(&m_d3d12Device));

            if (WIN_OK(hRes))
            {
                m_gpuDesc = GetGpuInfo(m_dxgiAdapter.Get());

                D3D12_FEATURE_DATA_SHADER_MODEL sm{ .HighestShaderModel{ D3D12_REQUIRED_SHADER_MODEL } };
                hRes = (m_d3d12Device->CheckFeatureSupport1(
                    D3D12_FEATURE_SHADER_MODEL,
                    &sm, 
                    sizeof(D3D12_FEATURE_DATA_SHADER_MODEL), 
                    D3D12_SDK_VERSION
                ));

                if (WIN_FAIL(hRes) || sm.HighestShaderModel < D3D12_REQUIRED_SHADER_MODEL)
                {
                    NF_LOG_WARNING("Graphics Card: {} {:.0f}GB doesn't meet requirements, must support Shader Model >= 6.6", m_gpuDesc.name, m_gpuDesc.dedicatedMemoryInGBs);
                    m_d3d12Device.Reset();
                    continue;
                }
                
                m_displaysDescs = GetAllConnectedDisplayDescriptions(m_dxgiAdapter.Get());

                NF_LOG_INFO("Graphics Card: {} {:.0f}GB", m_gpuDesc.name, m_gpuDesc.dedicatedMemoryInGBs);
                for (const auto& d : m_displaysDescs)
                    NF_LOG_INFO("Monitor: {} {}x{}@{}Hz", 
                        d.name, 
                        d.width, 
                        d.height, 
                        d.maxRefreshRate);

                NF_LOG_INFO("[DX12] Device created");

            #if defined(D3D_DEBUG)
                m_infoQueue.Initialize(m_d3d12Device.Get());
            #endif

                return;
            }
            else
            {
                m_d3d12Device.Reset();
                m_dxgiAdapter.Reset();
            }
        }

        m_dxgiAdapter.Reset();

        NF_ASSERT(false, "No GPU found that supports Feature Level 12_2 and Shader Model 6.6");
    }

    const GpuDesc& Device::GetGpuDescription() const
    {
        return m_gpuDesc;
    }

    const Vector<DisplayDesc> Device::GetDisplayDescriptions() const
    {
        return m_displaysDescs;
    }

    Vector<DisplayDesc> Device::GetAllConnectedDisplayDescriptions(IDXGIAdapterVer* pAdapter) noexcept
    {
        HRESULT hRes{};
        u32 i{ 0 };
        ComPtr<IDXGIOutput> outputV0{};

        Vector<DisplayDesc> descriptions;

        while ((hRes = pAdapter->EnumOutputs(i, outputV0.ReleaseAndGetAddressOf())) == S_OK)
        {
            ComPtr<IDXGIOutput6> output{};
            WIN_CHECK(outputV0.As<IDXGIOutput6>(&output));

            DXGI_OUTPUT_DESC1 outputDesc{};
            WIN_CHECK(output->GetDesc1(&outputDesc));

            String monitorName{ GetMonitorNameByDXGIName(outputDesc.DeviceName) };

            Vector<DisplayDesc::DisplayMode> modeLists{ GetDisplayModes(output.Get()) };

            DisplayDesc::DisplayMode& modeDesc{ modeLists.back() };
            i++;

            descriptions.emplace_back(
                DisplayDesc
                {
                    .name{ std::move(monitorName) },
                    .width{ modeDesc.width },
                    .height{ modeDesc.height },
                    .maxRefreshRate{ modeDesc.refreshRate },
                    .supportedModes { std::move(modeLists) }
                }
            );
        }
        return descriptions;
    }

    String Device::GetMonitorNameByDXGIName(WStringView DXGIName) noexcept
    {
        u32 pathCount{};
        u32 modeCount{};

        i32 result = GetDisplayConfigBufferSizes(
            QDC_ONLY_ACTIVE_PATHS,
            &pathCount,
            &modeCount
        );

        if (result != ERROR_SUCCESS)
            return "Unknown";

        Vector<DISPLAYCONFIG_PATH_INFO> paths(pathCount);
        Vector<DISPLAYCONFIG_MODE_INFO> modes(modeCount);

        result = QueryDisplayConfig(
            QDC_ONLY_ACTIVE_PATHS,
            &pathCount,
            paths.data(),
            &modeCount,
            modes.data(),
            nullptr
        );

        if (result != ERROR_SUCCESS)
            return "Unknown";

        paths.resize(pathCount);

        for (const DISPLAYCONFIG_PATH_INFO& path : paths)
        {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName
            {
                .header
                {
                    .type{DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME},
                    .size{sizeof(sourceName)},
                    .adapterId{path.sourceInfo.adapterId},
                    .id{path.sourceInfo.id}
                }
            };

            if (DisplayConfigGetDeviceInfo(&sourceName.header) != ERROR_SUCCESS)
                continue;

            if (DXGIName != sourceName.viewGdiDeviceName)
                continue;

            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName
            {
                .header
                {
                    .type{DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME},
                    .size{sizeof(targetName)},
                    .adapterId{path.targetInfo.adapterId},
                    .id{path.targetInfo.id}
                }
            };

            if (DisplayConfigGetDeviceInfo(&targetName.header) != ERROR_SUCCESS)
                return "Unknown";

            if (targetName.monitorFriendlyDeviceName[0] == L'\0')
                return "Unknown";


            return OS::Windows::WideToUtf8(targetName.monitorFriendlyDeviceName);
        }

        return "Unknown";
    }

    Vector<DisplayDesc::DisplayMode> D3D12::Device::GetDisplayModes(IDXGIOutput6* outputVer6) noexcept
    {
        u32 count{};
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

        // get count of modelists
        WIN_CHECK(outputVer6->GetDisplayModeList1(format, 0, &count, nullptr));

        // get the modelists
        Vector<DXGI_MODE_DESC1> modeLists(count);
        WIN_CHECK(outputVer6->GetDisplayModeList1(format, 0, &count, &modeLists[0]));

        Vector<DisplayDesc::DisplayMode> vec;

        for (const auto& modeDesc : modeLists)
        {
            vec.emplace_back(
                DisplayDesc::DisplayMode
                {
                    .width{ modeDesc.Width },
                    .height{ modeDesc.Height },
                    .refreshRate{ modeDesc.RefreshRate.Numerator / modeDesc.RefreshRate.Denominator }
                }
            );
        }

        return vec;
    }
    
    GpuDesc Device::GetGpuInfo(IDXGIAdapterVer* pAdapter) noexcept
    {
        DXGI_ADAPTER_DESC3 adapterDesc{};
        pAdapter->GetDesc3(&adapterDesc);

        auto gpuName = adapterDesc.Description;
        f32 dedicatedMemoryInGBs{ std::ceil((static_cast<f32>(adapterDesc.DedicatedVideoMemory) / (1 << 30))) };

        return GpuDesc
        {
            .name{ OS::Windows::WideToUtf8(gpuName) },
            .dedicatedMemoryInGBs{ dedicatedMemoryInGBs }
        };
    }
}