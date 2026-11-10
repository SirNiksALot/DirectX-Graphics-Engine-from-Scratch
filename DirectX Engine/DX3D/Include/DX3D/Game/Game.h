#pragma once
#include <chrono>
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>

namespace dx3d {
	class Game 
	{
		dx3d_disable_copy_and_move(Game);
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game();

		virtual World& getWorld() noexcept final;
		virtual Logger& getLogger() noexcept final;
		virtual void run() final; // The main game loop function
	private:
		void onInternalUpdate();
	private:
		UniquePtr<Logger> m_logger{};
		UniquePtr<GraphicsEngine> m_graphicsEngine{};
		UniquePtr<Display> m_display{};
		UniquePtr<World> m_world{};

		
		bool m_isRunning{ true };

		std::chrono::steady_clock::time_point m_previousTime{};

	protected:
		virtual void onCreate() {};
		virtual void onUpdate(f32 deltaTime) {};

	};

}
