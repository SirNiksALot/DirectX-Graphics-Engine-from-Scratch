#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc,const GraphicsResourceDesc& gDesc)
	:GraphicsResource(gDesc)
{
	if (desc.vs.getType() != ShaderType::VertexShader)
		DX3DLogThrowInvalidArg("The 'vs' member is not a valid vertex shader binary object");
	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogThrowInvalidArg("The 'ps' member is not a valid pixel shader binary object");

	// Creates Vertex and Pixel shader from compiled HLSL Bytecode
	auto vs = desc.vs.getData(); // retrieved Compiled bytecode and size as struct
	auto ps = desc.ps.getData(); // retrieved Compiled bytecode and size as struct

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
