#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d {
	class GraphicsEngine : public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;
		GraphicsDevice& getGraphicsDevice() noexcept;

		// This function will handle sending commands to GPU and writing to buffer using swapchain etc.
		void render(SwapChain& swapChain,f32 deltatime);

	private:
		struct Vertex {
			Vec3 position;
			Vec4 color;
		};

		struct alignas(16) ConstantData {
			f32 scale{};
		};

	private:
		RefPtr<GraphicsDevice> m_graphicsDevice{};
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr <GraphicsPipelineState> m_pipeline{};
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<ConstantBuffer> m_cb{};

		f32 m_sum{};
		f32 m_scale{};




	};
}

