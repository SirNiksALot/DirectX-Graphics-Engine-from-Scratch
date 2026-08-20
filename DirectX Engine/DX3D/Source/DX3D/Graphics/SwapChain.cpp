#include <DX3D/Graphics/SwapChain.h>




dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc)
{ 
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};
	dxgiDesc.BufferDesc.Width = std::max(1, desc.winSize.width);
	dxgiDesc.BufferDesc.Height = std::max(1, desc.winSize.height);
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	// the "8" in R8G8B8A8 means 8 bit channel . 
	// and UNORM means the RGBA values have been normalized to the 0 - 1 range.
	dxgiDesc.BufferCount = 2; // How many back buffers we want
	// When we use windows DWM the buffer count only represents the back buffers because,
	// the front buffer is represented by the Desktop itself
	// but when we are using full screen mode , back buffer and front buffer counts should be included
	// in .BufferCount
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	// Tells DXGI to use the buffer as a render target
	dxgiDesc.OutputWindow = static_cast<HWND>(desc.winHandle);
	dxgiDesc.SampleDesc.Count = 1; // for now we dont need it so we set it to 1
	// sample counter for multi-sample anti-aliasing
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ⚠️ Look into this
	// swap effect "FLIP DISCARD" instead of copying buffer for displaying it is flipped and swapped because of shared memory
	dxgiDesc.Windowed = TRUE;



	DX3DGraphicsLogErrorAndThrow(m_factory.CreateSwapChain(&m_device, &dxgiDesc, &m_swapChain),
		"CreateSwapChain Failed."
		);
}
