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

		virtual Logger& getLogger() noexcept final;
		virtual void run() final; // The main game loop function
	private:
		void onInternalUpdate();
	private:
		UniquePtr<Logger> m_logger{};
		UniquePtr<GraphicsEngine> m_graphicsEngine{};
		UniquePtr<Display> m_display{};
		// smart pointer approach , automatically deleted this object when Destructor is called , so that we dont need to write ```delete m_handle``` in the destructor
		
		
		bool m_isRunning{ true };

		std::chrono::steady_clock::time_point m_previousTime{};

	};

}
