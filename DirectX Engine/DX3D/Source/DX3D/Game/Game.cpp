#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/World.h>

dx3d::Game::Game(const GameDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.logLevel);

	DX3DLogInfo("DX3D11 Engine logger");
	DX3DLogInfo("--------------------------------------");

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{*m_logger});
	m_display = std::make_unique<Display>(DisplayDesc{ *m_logger , desc.windowSize , m_graphicsEngine->getGraphicsDevice() });
	m_world = std::make_unique<World>(WorldDesc{ {*m_logger} });

	DX3DLogInfo("Game Initialized");

}

dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
}


void dx3d::Game::onInternalUpdate()
{
	// calculating delta time ( time between frames ) --------------------------
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<f32> delta = currentTime - m_previousTime;
	m_previousTime = currentTime; // for next game loop iteration 
	auto deltaTime = delta.count();

	onUpdate(deltaTime);
	m_world->update(deltaTime);

	m_graphicsEngine->render(m_display->getSwapChain(),deltaTime);
}

dx3d::World& dx3d::Game::getWorld() noexcept
{
	return *m_world;
}

dx3d::Logger& dx3d::Game::getLogger() noexcept
{
	return *m_logger;
}
