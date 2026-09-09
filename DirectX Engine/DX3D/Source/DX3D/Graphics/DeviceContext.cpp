#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>

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

void dx3d::DeviceContext::setGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	// this method sets input layout to Input assembler ( IA ) of GPU pipeline
	m_context->IASetInputLayout(pipeline.m_layout.Get());

	// this method binds a Vertext shader to the GPU pipeline
	m_context->VSSetShader(pipeline.m_vs.Get()
		,nullptr,0); // these 2 args are for dynamic shader linking ( but we will not be using hence null ) 
	// similarly for Pixel shader
	m_context->PSSetShader(pipeline.m_ps.Get(), nullptr, 0);
}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
	auto buf = buffer.m_buffer.Get(); // return pointer to vertex buffer
	auto stride = buffer.m_vertexSize;
	auto offset = 0u;

	m_context->IASetVertexBuffers(
	0, // pointer to start to list of vertex buffers ( but we only use 1 VB so we pass null ) 
	1, // number of VBs
	&buf, // pointer to list of VBs
	&stride, // size of single vertex in bytes
	&offset // offset to say from where to start processing the data ( since we dont do anything with offsets we set it to unsigned int 0 ) 
	);
	// this functions binds one or more vertex buffers to the input assembler ( IA ) stage of GPU pipeline
}


// sets viewport where our geometry will be rasterized on the screen
void dx3d::DeviceContext::setViewPortSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<f32>(size.width);
	vp.Height = static_cast<f32>(size.height);
	vp.MinDepth = 0.0f ; // near clipping plain
	vp.MinDepth = 1.0f; // far clipping plain

	m_context->RSSetViewports(0, &vp);
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	// this function decides how IA interprets vertex data ( tells IA to draw a triangle from data ) 
	m_context->IASetPrimitiveTopology(
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST // every group of 3 vertices will be treated as an independent triangle
	);

	m_context->Draw(vertexCount, startVertexLocation);
}

