#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Math/Vec3.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc):Base(desc.base)
{

	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext =  device.createDeviceContext();


	constexpr char shaderSourceCode[] =
		R"(
void VSMain()
{
}
void PSMain()
{
}
)";
	constexpr char shaderSourceName[] = "Basic";
	constexpr auto shaderSourceCodeSize = std::size(shaderSourceCode);


	auto vs = device.compileShader({
		shaderSourceName,
		shaderSourceCode,
		shaderSourceCodeSize,
		"VSMain", 
		ShaderType::VertexShader });


	auto ps = device.compileShader({
		shaderSourceName,
		shaderSourceCode,
		shaderSourceCodeSize,
		"PSMain", 
		ShaderType::PixelShader });

	m_pipeline = device.createGraphicsPipelineState({ *vs,*ps });


	const Vec3 vertexList[] = {
		{-0.5f,-0.5f,0.0f},
		{0.0f,0.5f,0.0f},
		{0.5f,-0.5f,0.0f},

	};
	m_vb = device.createVertexBuffer({vertexList,std::size(vertexList),sizeof(Vec3)});
}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	// STEP 1 : Collect all commands in Deffered context --------------------------------------------
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, {1,0,0,1}); // Red set to 1 and opacity 1 (100%) . G and B to 0.

	// STEP 2 : Set Graphics pipeline to add your Vertex and pixel shader to GPU pipeline
	context.setGraphicsPipelineState(*m_pipeline);

	// STEP 3 : Set Vertex buffer to pipeline --------------------------------------------------------
	auto& vb = *m_vb;
	context.setVertexBuffer(vb);

	// STEP 3 : Execute command list using immediate context inside GraphicsDevice ------------------
	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);

	// STEP 4 : Present Back buffer to Front buffer -------------------------------------------------
	swapChain.present();

}
