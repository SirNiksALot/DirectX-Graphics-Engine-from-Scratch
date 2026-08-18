#include <DX3D/Graphics/SwapChain.h>




dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResource& gDesc):
	GraphicsResource(gDesc)
{ 
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};
	//dxgiDesc.BufferDesc.Width = 

	m_factory.CreateSwapChain(&m_device);
}
