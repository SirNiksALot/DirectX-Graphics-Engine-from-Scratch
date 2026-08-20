#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <d3d11.h>
#include <wrl.h>
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class RenderSystem : public Base
	{
	public:
		explicit RenderSystem(const RenderSystemDesc& desc);
		virtual ~RenderSystem() override;

		SwapChainPtr createSwapChain(const SwapChainDesc& desc);

	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{}; // D3D11 Device ⭐. It uses reference memory counting for memory management and thats why we use COM pointer and not smart pointers here 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{}; // D3D11 Device Context ⭐
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{}; // DXGI Device ⭐
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{}; // DXGI Adapter ⭐
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{}; // DXGI Adapter ⭐

	};
}

