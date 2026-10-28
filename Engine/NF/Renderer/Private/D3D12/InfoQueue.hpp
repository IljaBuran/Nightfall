#pragma once

#include "Private/D3D12/D3D12Include.hpp"

#include <Core/Diagnostics/Assert.hpp>
#include <Core/Utility/Helpers.hpp>

#include <magic_enum/magic_enum.hpp>

// overriding search range
template<>
struct magic_enum::customize::enum_range<D3D12_MESSAGE_ID>
{
    static constexpr int min =
        static_cast<int>(D3D12_MESSAGE_ID_UNKNOWN);

    static constexpr int max =
        static_cast<int>(D3D12_MESSAGE_ID_D3D12_MESSAGES_END);
};

namespace NF::RendererApi::D3D12
{
    class InfoQueue
    {
    public:

        NF_NOCOPY(InfoQueue);
        NF_NOMOVE(InfoQueue);

        InfoQueue() = default;

        void Initialize(ID3D12DeviceVer* const device);
        void Destroy();


    private:

        static StringView GetCategoryString(D3D12_MESSAGE_CATEGORY category);
        static StringView GetIdString(D3D12_MESSAGE_ID messageId);

        static void CallbackFunction(
            D3D12_MESSAGE_CATEGORY category, 
            D3D12_MESSAGE_SEVERITY severity, 
            D3D12_MESSAGE_ID id, 
            LPCSTR pDescription, 
            void* pContext
        );

    private:
        ComPtr<ID3D12InfoQueueVer> m_infoQueue;
        DWORD                      m_infoQueueCallbackCookie{};
    };
}