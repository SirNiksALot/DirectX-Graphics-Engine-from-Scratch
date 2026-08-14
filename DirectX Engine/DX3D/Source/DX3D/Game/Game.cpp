#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>

dx3d::Game::Game(const GameDesc& desc):Base({ *std::make_unique<Logger>(desc.logLevel).release()}),
	m_loggerPtr(&m_logger) 
	// 👆 because the Base() initialization means the logger is only accessible in the base class , 
	// therefore we need to reinject it back to Game Class.

{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger});
	m_display = std::make_unique<Window>(WindowDesc{m_logger});

	m_loggerPtr->log(Logger::LogLevel::Info,"Game Initialized");
}

dx3d::Game::~Game()
{
	m_loggerPtr->log(Logger::LogLevel::Info, "Game deallocation started");
}

