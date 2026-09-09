#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>
namespace dx3d {
	class DeviceContext: public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc);
		~DeviceContext();

		void clearAndSetBackBuffer(const SwapChain& swapChain,const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
		void setVertexBuffer(const VertexBuffer& buffer);
		void setViewPortSize(const Rect& size); 

		void drawTriangleList(ui32 vertexCount, ui32 startVertexLocation);

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

		friend class GraphicsDevice;

	};
}

