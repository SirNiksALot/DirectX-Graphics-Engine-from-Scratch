#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexShaderSignature.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc,const GraphicsResourceDesc& gDesc)
	:GraphicsResource(gDesc)
{
	// STEP 0 : -------------------- validation -----------------------------------------------
	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogThrowInvalidArg("The 'ps' member is not a valid pixel shader binary object");




	// STEP 1 -------------- Gather args for creating VS and PS  ------------------------------
	auto vs = desc.vs.getShaderBinaryData(); // retrieved Compiled bytecode and size as struct
	auto ps = desc.ps.getData(); // retrieved Compiled bytecode and size as struct





	// STEP 2 ----------------- creating input layout -----------------------------------------
	// Purpose :  to allow for the vertex shader to understand the vertex data in vertex buffer 
	

	auto vsInputElements = desc.vs.getInputElementsData();

	DX3DGraphicsLogThrowOnFail( m_device.CreateInputLayout(
		static_cast<const D3D11_INPUT_ELEMENT_DESC*>(vsInputElements.data),
		static_cast<ui32>(vsInputElements.dataSize),
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
