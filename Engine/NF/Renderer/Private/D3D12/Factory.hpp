#pragma once

#include "Private/D3D12/D3D12Include.hpp"

#include <Core/Diagnostics/Assert.hpp>
#include <Core/Utility/Helpers.hpp>

namespace NF::RendererApi::D3D12
{
	class Factory
	{
	public:

		NF_NOCOPY(Factory);
		NF_NOMOVE(Factory);

		Factory();

		[[nodiscard]]
		IDXGIFactoryVer* GetFactoryPtr()
		{
			NF_ASSERT(m_dxgiFactory);
			return m_dxgiFactory.Get();
		}

		[[nodiscard]]
		IDXGIFactoryVer* operator->()
		{
			return GetFactoryPtr();
		}

		[[nodiscard]]
		operator IDXGIFactoryVer* ()
		{
			return m_dxgiFactory.Get();
		}

	private:

		ComPtr<IDXGIFactoryVer> m_dxgiFactory;
	};
}