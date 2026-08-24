#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
namespace dx3d {
	class DeviceContext: public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc);
		~DeviceContext();

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

	};
}

