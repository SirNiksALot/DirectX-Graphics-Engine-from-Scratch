#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class VertexBuffer : public GraphicsResource
	{
	public:
		VertexBuffer(const VertexBufferDesc& desc ,const GraphicsResourceDesc& gDesc);
	

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		ui32 m_vertexSize{};
		friend class DeviceContext;
	
	};
}

