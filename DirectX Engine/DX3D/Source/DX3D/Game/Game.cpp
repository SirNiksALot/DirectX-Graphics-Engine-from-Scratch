#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>

dx3d::Game::Game()
{
	m_loggerPtr = std::make_unique<Logger>();
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>();

	m_loggerPtr->log(Logger::LogLevel::Info,"Game Initialized");
}

dx3d::Game::~Game()
{
	m_loggerPtr->log(Logger::LogLevel::Info, "Game deallocation started");
}

