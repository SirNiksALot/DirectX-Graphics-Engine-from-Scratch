#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>

namespace dx3d {
	class Game : public Base
	{
		public:
			explicit Game(const GameDesc& desc);
			virtual ~Game() override;

			virtual void run() final; // The main game loop function
	private:
		std::unique_ptr<Logger> m_loggerPtr{};
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{};
		std::unique_ptr<Window> m_display{}; 
		// smart pointer approach , automatically deleted this object when Destructor is called , so that we dont need to write ```delete m_handle``` in the destructor
		
		
		bool m_isRunning{ true };

	};

}
