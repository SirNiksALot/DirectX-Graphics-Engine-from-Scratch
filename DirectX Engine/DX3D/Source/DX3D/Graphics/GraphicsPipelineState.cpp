#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc,const GraphicsResourceDesc& gDesc)
	:GraphicsResource(gDesc)
{
	// STEP 0 : -------------------- validation -----------------------------------------------
	if (desc.vs.getType() != ShaderType::VertexShader)
		DX3DLogThrowInvalidArg("The 'vs' member is not a valid vertex shader binary object");
	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogThrowInvalidArg("The 'ps' member is not a valid pixel shader binary object");




	// STEP 1 -------------- Gather args for creating VS and PS  ------------------------------
	auto vs = desc.vs.getData(); // retrieved Compiled bytecode and size as struct
	auto ps = desc.ps.getData(); // retrieved Compiled bytecode and size as struct





	// STEP 2 ----------------- creating input layout -----------------------------------------
	// Purpose :  to allow for the vertex shader to understand the vertex data in vertex buffer 
	constexpr D3D11_INPUT_ELEMENT_DESC elements[] =
	{
		{
			"POSITION", // name of "semantic" used in HLSL code
			0, // used to differentiate multiple var using the same semantic name ( we dont need this ,so 0 )
			DXGI_FORMAT_R32G32B32_FLOAT, // we use float3 to define positions hence this dxgi format
			0, // index of vertex buffer from vertex buffer list the element comes from 
			0, // buffer offset ( position is the first data we encounter in the buffer so, 0 
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};
	DX3DGraphicsLogThrowOnFail( m_device.CreateInputLayout(
		elements,
		std::size(elements),
		vs.data,
		vs.dataSize,
		&m_layout // output param ( input layout object ) 
		),"CreateInputLayout failed");







	// STEP 3  ------- Creates Vertex and Pixel shader from compiled HLSL Bytecode -------------
	DX3DGraphicsLogThrowOnFail(m_device.CreateVertexShader(
		vs.data, 
		vs.dataSize,
		nullptr,
		&m_vs 
	),"CreateVertexShader Failed.");

	DX3DGraphicsLogThrowOnFail(m_device.CreatePixelShader(
		ps.data,
		ps.dataSize,
		nullptr,
		&m_ps
	), "CreatePixelShader Failed.");

	
}
