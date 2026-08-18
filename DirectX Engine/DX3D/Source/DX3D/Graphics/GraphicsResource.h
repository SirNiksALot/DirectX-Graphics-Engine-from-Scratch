#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <d3d11.h>

namespace dx3d {

	struct GraphcisResourceDesc {
		BaseDesc base;
		ID3D11Device& device;
		IDXGIFactory& factory;
	};



	class GraphicsResource : public Base {
		public :
			explicit GraphicsResource(const GraphcisResourceDesc& desc) :
				Base(desc.base),
				m_device(desc.device),
				m_factory(desc.factory)
			{
			}

	protected:
		ID3D11Device& m_device;
		IDXGIFactory& m_factory;

	};
}