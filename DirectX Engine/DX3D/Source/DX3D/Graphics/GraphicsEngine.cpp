#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <fstream>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/IndexBuffer.h>


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
		{{-0.5f,-0.5f,-0.5f}, {1,0,0,1}},
		{{-0.5f,0.5f,-0.5f}, {0,1,0,1} },
		{{0.5f,0.5f,-0.5f},  {0,0,1,1}},
		{{0.5f,-0.5f,-0.5f}, {1,0,1,1}},

		{{0.5f,-0.5f,0.5f}, {1,0,1,1}},
		{{0.5f,0.5f,0.5f}, {0,0,1,1}},
		{{-0.5f,0.5f,0.5f}, {0,1,0,1}},
		{{-0.5f,-0.5f,0.5f}, {1,0,0,1}}
	};
	m_vb = device.createVertexBuffer({vertexList,std::size(vertexList),sizeof(Vertex)});

	// Create Index buffer 
	// ----------------------------------------------------------------------------------------
	const ui32 indexList[] =
	{
		//winding order: clockwise
		// 
		//front face indices
		0,1,2,  //first triangle
		2,3,0,  //second triangle
		//back face indices
		4,5,6,
		6,7,4,
		//top face indices
		1,6,5,
		5,2,1,
		//bottom face indices
		7,0,3,
		3,4,7,
		//right face indices
		3,2,5,
		5,4,3,
		//left face indices
		7,6,1,
		1,0,7
	};
	m_ib = device.createIndexBuffer({ indexList,std::size(indexList) });


	// Create constant buffer
	// ----------------------------------------------------------------------------------------
	m_cb = device.createConstantBuffer({ {},sizeof(ConstantData)});

}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

dx3d::GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
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
	m_pos += deltatime * 0.0f;
	m_rot += deltatime * 0.707f; 
	m_scale = std::abs(std::sin(m_rot)); 
	/*
	* m_rot keeps increaing, sin(m_rot) fluctuates between 1 and -1
	* abs(sin(m_rot)) keeps fluctuating between 0 and 1 
	* Therefore scale keeps fluctuating between 0 and 1
	*/ 

	auto worldMat =
		Mat4x4::scale({ m_scale,m_scale,m_scale }) *
		Mat4x4::rotateX(m_rot) *
		Mat4x4::rotateY(m_rot) *
		Mat4x4::rotateZ(m_rot) *
		Mat4x4::translate({ m_pos,m_pos,0 });

	//orthographic camera setup
	auto size = swapChain.getSize();
	auto aspect = static_cast<f32>(size.width) / size.height;
	auto unitsPerScreenHeight = 2.0f;
	auto viewHeight = unitsPerScreenHeight;
	auto viewWidth = unitsPerScreenHeight * aspect;

	ConstantData data{
		worldMat,
		Mat4x4::orthoLH(viewWidth,viewHeight,-10.0f,10.0f)
	};

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

	// STEP 7 : Draw triangle ( old )  -----------------------------------------------------------------
	//context.drawTriangleList(
	//	vb.getVertexListSize(),
	//	0u // start processing from the first vertex
	//	);

	// STEP 8 : Set index buffer and Draw indexed triangle list -------------------------------------
	auto& ib = *m_ib;

	context.setIndexBuffer(ib);

	context.drawIndexedTriangleList(
		ib.getIndexListSize(),
		0u,
		0u
	);

	// STEP 8 : Execute command list using immediate context inside GraphicsDevice ------------------
	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);

	// STEP 9 : Present Back buffer to Front buffer -------------------------------------------------
	swapChain.present();

}
