#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.logLevel);

	DX3DLogInfo("DX3D11 Engine logger");
	DX3DLogInfo("--------------------------------------");

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{*m_logger});
	m_display = std::make_unique<Display>(DisplayDesc{ *m_logger , desc.windowSize , m_graphicsEngine->getGraphicsDevice() });

	DX3DLogInfo("Game Initialized");

}

dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
}


void dx3d::Game::onInternalUpdate()
{
	m_graphicsEngine->render(m_display->getSwapChain());
}

dx3d::Logger& dx3d::Game::getLogger() noexcept
{
	return *m_logger;
}
