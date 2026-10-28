#include <Private/pch.hpp>

#include "Private/D3D12/Helpers.hpp"


namespace NF::RendererApi::D3D12
{
    Vector<Utility::DisplayDesc::DisplayMode> GetDisplayModes(IDXGIOutput6* outputVer6)
    {
        u32 count{};
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

        // get count of modelists
        WIN_CHECK(outputVer6->GetDisplayModeList1(format, 0, &count, nullptr));

        // get the modelists
        Vector<DXGI_MODE_DESC1> modeLists(count);
        WIN_CHECK(outputVer6->GetDisplayModeList1(format, 0, &count, &modeLists[0]));

        Vector<Utility::DisplayDesc::DisplayMode> vec;

        for (const auto& modeDesc : modeLists)
        {
            vec.emplace_back(
                Utility::DisplayDesc::DisplayMode
                {
                    .width{ modeDesc.Width },
                    .height{ modeDesc.Height },
                    .refreshRate{ modeDesc.RefreshRate.Numerator / modeDesc.RefreshRate.Denominator }
                }
            );
        }

        return vec;
    }

    [[nodiscard]]
    String GetMonitorNameByDXGIName(WStringView DXGIName) noexcept
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
}

