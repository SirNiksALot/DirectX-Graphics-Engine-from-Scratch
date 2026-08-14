#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>

namespace dx3d {
	class GraphicsEngine : public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

	private:
		std::unique_ptr<RenderSystem> m_renderSystem{};


	};
}

