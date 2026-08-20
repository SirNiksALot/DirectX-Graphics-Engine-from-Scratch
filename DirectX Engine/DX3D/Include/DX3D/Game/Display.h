#pragma once
#include <DX3D/Window/Window.h>

namespace dx3d {
	// This class is the place where we render all our 3d graphics
	class Display : public Window
	{
	public:
		explicit Display(const DisplayDesc& desc);

	private:
		SwapChainPtr m_swapChain{};
	};


}