#include "Private/pch.hpp"

#include "Private/D3D12/InfoQueue.hpp"

#include <Core/STL/Format.hpp>

namespace NF::RendererApi::D3D12
{
    void InfoQueue::Initialize(ID3D12DeviceVer* const device)
    {
        NF_ASSERT(device);

        WIN_CHECK(device->QueryInterface(IID_PPV_ARGS(&m_infoQueue)));
        WIN_CHECK(m_infoQueue->RegisterMessageCallback(
            CallbackFunction,
            D3D12_MESSAGE_CALLBACK_FLAG_NONE,
            nullptr, &m_infoQueueCallbackCookie));

        NF_ASSERT(m_infoQueueCallbackCookie);

        NF_LOG_INFO("[DX12] Debug InfoQueue created and message callback registered");
    }

    void InfoQueue::Destroy()
    {
        if (m_infoQueue)
        {
            m_infoQueue->UnregisterMessageCallback(m_infoQueueCallbackCookie);
            m_infoQueueCallbackCookie = 0;
        }
    }

    StringView InfoQueue::GetCategoryString(D3D12_MESSAGE_CATEGORY category)
    {
        constexpr StringView prefix = "D3D12_MESSAGE_CATEGORY_";

        StringView name = magic_enum::enum_name(category);

        if (name.empty())
            return "Unknown";

        if (name.starts_with(prefix))
            name.remove_prefix(prefix.size());

        return name;
    }

    StringView InfoQueue::GetIdString(D3D12_MESSAGE_ID messageId)
    {
        constexpr StringView prefix = "D3D12_MESSAGE_ID_";

        StringView name = magic_enum::enum_name(messageId);

        if (name.empty())
            return "Unknown";

        if (name.starts_with(prefix))
            name.remove_prefix(prefix.size());

        return name;
    }

    void InfoQueue::CallbackFunction(
        D3D12_MESSAGE_CATEGORY category, 
        D3D12_MESSAGE_SEVERITY severity, 
        D3D12_MESSAGE_ID id, 
        LPCSTR pDescription, 
        [[maybe_unused]] void* pContext
    )
    {
        using LogLevel = ::NF::Logging::Level;
        LogLevel logLevel{};
        switch (severity)
        {
            case D3D12_MESSAGE_SEVERITY_CORRUPTION:
                [[fallthrough]];
            case D3D12_MESSAGE_SEVERITY_ERROR:
            {
                logLevel = LogLevel::Error;
                break;
            }
            case D3D12_MESSAGE_SEVERITY_WARNING:
            {
                logLevel = LogLevel::Warning;
                break;
            }
            case D3D12_MESSAGE_SEVERITY_MESSAGE:
                [[fallthrough]];
            case D3D12_MESSAGE_SEVERITY_INFO:
            {
                logLevel = LogLevel::Info;
                break;
            }
        }
        String desc(pDescription);

        String str = Format(
            "Category: {}\n"
            "ID: {}\n"
            "Description: {}",
            InfoQueue::GetCategoryString(category),
            InfoQueue::GetIdString(id),
            desc
        );

        ::NF::Logging::Write(logLevel, str);
    }
}