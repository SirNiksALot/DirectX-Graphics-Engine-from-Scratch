#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDefferedContext Failed."
		);
}

dx3d::DeviceContext::~DeviceContext()
{
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	f32 fColor[] = { color.x,color.y,color.z,color.w };
	/*
	A RenderTargetView in D3D11 is basically referring to the block of memory that represents
	Pixel data that will ultimately be rendered.
	This "RenderTargetView" in our case is the block of memory i.e. back buffer managed by the swapchain.
	Therefore we need to wrap our back buffer in a RenderTargetView so that the device context can interface with it 
	using ClearRenderTargetView
	*/
	auto rtv = swapChain.m_rtv.Get();
	m_context->ClearRenderTargetView(rtv,fColor);
	m_context->OMSetRenderTargets(
		1,
		&rtv, // we simulate an array by passing the address of the rtv ( like how array names hold the address to the first element ) 
		nullptr);
}

