#pragma once

#include "Private/D3D12/D3D12Include.hpp"

#include "Renderer/Utility.hpp"

#include <Core/Diagnostics/Assert.hpp>
#include <Core/Utility/Helpers.hpp>
#include <Core/STL/Vector.hpp>

namespace NF::RendererApi::D3D12
{
    using namespace Utility;

    class Device
    {
    public:

        NF_NOCOPY(Device);
        NF_NOMOVE(Device);
        
        Device() = default;
        
        void Create(IDXGIFactoryVer* factory);

        [[nodiscard]]
        ID3D12DeviceVer* GetDevicePtr()
        {
            NF_ASSERT(m_d3d12Device);
            return m_d3d12Device.Get();
        }

        [[nodiscard]]
        IDXGIAdapterVer* GetAdapterPtr()
        {
            NF_ASSERT(m_dxgiAdapter);
            return m_dxgiAdapter.Get();
        }

        [[nodiscard]]
        ID3D12DeviceVer* operator->()
        {
            return GetDevicePtr();
        }

        [[nodiscard]]
        operator ID3D12DeviceVer*()
        {
            return GetDevicePtr();
        }

        [[nodiscard]]
        const GpuDesc& GetGpuDescription() const;
        
        [[nodiscard]]
        const Vector<DisplayDesc> GetDisplayDescriptions() const;

    private:

        [[nodiscard]] static
        Vector<DisplayDesc> GetAllConnectedDisplayDescriptions(IDXGIAdapterVer* pAdapter) noexcept;

        [[nodiscard]] static
        String GetMonitorNameByDXGIName(WStringView DXGIName) noexcept;

        [[nodiscard]] static
        Vector<DisplayDesc::DisplayMode> GetDisplayModes(IDXGIOutput6* outputVer6) noexcept;

        [[nodiscard]] static
        GpuDesc GetGpuInfo(IDXGIAdapterVer* pAdapter) noexcept;

    private:

        ComPtr<ID3D12DeviceVer> m_d3d12Device;
        ComPtr<IDXGIAdapterVer> m_dxgiAdapter;

        GpuDesc             m_gpuDesc;
        Vector<DisplayDesc> m_displaysDescs;
    };
}