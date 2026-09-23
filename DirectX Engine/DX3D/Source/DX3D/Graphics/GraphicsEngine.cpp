#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <fstream>
using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc):Base(desc.base)
{
	// Create GraphicsDevice and DeviceContext
	// ----------------------------------------------------------------------------------------
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext =  device.createDeviceContext();


	// Read HLSL file to load HLSL source code 
	// ----------------------------------------------------------------------------------------
	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowInvalidArg("Failed to open shader file");
	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>(),
	};
	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();;


	// Compile HLSL
	// ----------------------------------------------------------------------------------------
	auto vs = device.compileShader({
		shaderFilePath,
		shaderSourceCode,
		shaderSourceCodeSize,
		"VSMain", 
		ShaderType::VertexShader });


	auto ps = device.compileShader({
		shaderFilePath,
		shaderSourceCode,
		shaderSourceCodeSize,
		"PSMain", 
		ShaderType::PixelShader });


	// Create VertexShaderSignature ( for getting input layout elements ) 
	// ----------------------------------------------------------------------------------------
	auto vsSig = device.createVertexSignature({ vs });



	// Instantiate GraphicsPipelineState 
	// ----------------------------------------------------------------------------------------
	m_pipeline = device.createGraphicsPipelineState({ *vsSig,*ps });



	// Create vertex buffer
	// ----------------------------------------------------------------------------------------
	const Vertex vertexList[] = {
		{ {-0.5f, -0.5f, 0.0f}, {1,0,0,1} },
		{ {-0.5f, 0.5f, 0.0f}, {0,1,0,1} },
		{ {0.5f, 0.5f, 0.0f}, {0,0,1,1} },

		{ {0.5f, 0.5f, 0.0f}, {0,0,1,1} },
		{ {0.5f, -0.5f, 0.0f}, {1,0,1,1} },
		{ {-0.5f, -0.5f, 0.0f}, {1,0,0,1} }
	};
	m_vb = device.createVertexBuffer({vertexList,std::size(vertexList),sizeof(Vertex)});

	// Create constant buffer
	// ----------------------------------------------------------------------------------------
	m_cb = device.createConstantBuffer({ {},sizeof(ConstantData)});

}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}


void dx3d::GraphicsEngine::render(SwapChain & swapChain, f32 deltatime)
{
	// Collect all commands in Deffered context m_deviceContent ⭐ and,
	// then execute commands collected in deffered context using 
	// m_graphicsDevice's immediate context.

	auto& context = *m_deviceContext; // deferred context

	// STEP 1 : Update constant bffer ------------------------------------------------------------
	auto& cb = *m_cb;
	m_sum += deltatime * 3.0f;
	m_scale = std::abs(std::sin(m_sum));
	ConstantData data{};
	data.scale = m_scale;
	context.updateConstantBuffer(cb,&data);


	// STEP 2 : Clear the buffer with a color ------------------------------------------------------
	context.clearAndSetBackBuffer(swapChain, {0.55f,0.39f,0.55f,1.0f});

	// STEP 3 : Set Graphics pipeline to add your Vertex and pixel shader to GPU pipeline ---------
	context.setGraphicsPipelineState(*m_pipeline);

	// STEP 4 : Set viewport size 
	context.setViewPortSize(swapChain.getSize());

	// STEP 5 : Set Vertex buffer to pipeline --------------------------------------------------------
	auto& vb = *m_vb;
	context.setVertexBuffer(vb);

	// STEP 6 : Set Constant buffer to pipeline --------------------------------------------------------
	context.setConstantBuffer(cb);

	// STEP 7 : Draw triangle ------------------------------------------------------------------------
	context.drawTriangleList(
		vb.getVertexListSize(),
		0u // start processing from the first vertex
		);

	// STEP 8 : Execute command list using immediate context inside GraphicsDevice ------------------
	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);

	// STEP 9 : Present Back buffer to Front buffer -------------------------------------------------
	swapChain.present();

}
