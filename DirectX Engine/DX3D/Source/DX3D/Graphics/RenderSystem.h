#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <d3d11.h>
#include <wrl.h>

namespace dx3d {
	class RenderSystem : public Base
	{
	public:
		RenderSystem();
		virtual ~RenderSystem() override;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{}; // D3D11 Device ⭐. It uses reference memory counting for memory management and thats why we use COM pointer and not smart pointers here 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{}; // D3D11 Device Context ⭐
	};
}

