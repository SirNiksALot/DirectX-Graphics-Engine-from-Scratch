#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>

dx3d::GraphicsEngine::GraphicsEngine()
{
	m_renderSystem = std::make_unique<RenderSystem>();
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}
