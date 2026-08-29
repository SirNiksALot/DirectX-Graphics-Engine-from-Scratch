#pragma once
#include <DX3D/Graphics/GraphicsResource.h>


namespace dx3d {
	class SwapChain final : public GraphicsResource
	{
	public:
		SwapChain(const SwapChainDesc& desc,const GraphicsResourceDesc& gDesc);

		void present(bool vsync = false);

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv{}; // will get populated when reloadBuffers() runs.
		void reloadBuffers();

		friend class DeviceContext;

	};
}

