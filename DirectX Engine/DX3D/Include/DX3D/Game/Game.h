#pragma once
#include <DX3D/Core/Base.h>

namespace dx3d {
	class Game : public Base
	{
		public:
			Game();
			virtual ~Game();

			virtual void run() final;
	};

}
