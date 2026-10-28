#include "Private/pch.hpp"

#include "Private/D3D12/Factory.hpp"

namespace NF::RendererApi::D3D12
{
	Factory::Factory()
	{
		UINT factoryFlags{ 0 };
	
	#if defined(D3D_DEBUG)
		factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
	#endif
		
		WIN_CHECK(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&m_dxgiFactory)));
	}
}

