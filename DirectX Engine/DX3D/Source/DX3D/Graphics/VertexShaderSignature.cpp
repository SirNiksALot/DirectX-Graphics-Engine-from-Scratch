#include <DX3D/Graphics/VertexShaderSignature.h>
#include <d3dcompiler.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <ranges>
#include <DX3D/Graphics/GraphicsUtils.h>

dx3d::VertexShaderSignature::VertexShaderSignature(const VertexShaderSignatureDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc) , m_vsBinary(desc.vsBinary)
{
	if(!desc.vsBinary) DX3DLogThrowInvalidArg("No shader binary provided.");
	if(desc.vsBinary->getType() != ShaderType::VertexShader)
		DX3DLogThrowInvalidArg("vsBinary is not a valid vertex shader binary");

	auto vsData = m_vsBinary->getData();

	// Function to automatically extract metadata from compiled HLSL data.
	// Like input/output signatures , constant buffers and so on.
	// We use it to get the vertex's type
	DX3DGraphicsLogThrowOnFail(D3DReflect(
		vsData.data,
		vsData.dataSize,
		IID_PPV_ARGS(&m_shaderReflection) // output param : interface where shader metadata will be populated 
	), "D3DReflect failed.");

	D3D11_SHADER_DESC shaderDesc{};

	DX3DGraphicsLogThrowOnFail(
		m_shaderReflection->GetDesc(&shaderDesc), // get shader metadata from interface to descriptor
		"GetDesc failed from ID3D11ShaderReflection.");


	m_numElements = shaderDesc.InputParameters;
	D3D11_SIGNATURE_PARAMETER_DESC params[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{}; 
	/*
	D3D11_STANDARD_VERTEX_ELEMENT_COUNT = 32 because D3D11 lets you have a maximum of 
	32 vertex input elements for a vertex shader.
	Therefore we can safely define this size, rather than getting this dynamically.
	*/

	for (auto i : std::views::iota(0u, m_numElements)) {
		DX3DGraphicsLogThrowOnFail(
			m_shaderReflection->GetInputParameterDesc(i, &params[i])
		, "GetInputParameterDesc from ID3D11ShaderReflection failed."
		);
	}

	for (auto i : std::views::iota(0u, m_numElements)) {
		auto param = params[i];
		m_elements[i] = {
			param.SemanticName,
			param.SemanticIndex,
			GraphicsUtils::GetDXGIFormatFromMask(param.ComponentType,param.Mask),
			0,
			D3D11_APPEND_ALIGNED_ELEMENT, // macro to calculate offset automatically.
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};
	}

	/*
	Old method of creating input element desc was to manually write the desc like below 👇
	//Current vertext shader input struct looks like this : 
	//float3 position : POSITION0;
	//float4 color : COLOR0;
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
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			12, // offset is 12 because : color comes 12 bytes after position ( 3 floats of each 4 bytes )
			D3D11_INPUT_PER_VERTEX_DATA,
			0,
		}

	};
	*/




}

dx3d::BinaryData dx3d::VertexShaderSignature::getShaderBinaryData() const noexcept
{
	return m_vsBinary->getData();
}

dx3d::BinaryData dx3d::VertexShaderSignature::getInputElementsData() const noexcept
{
	return {
		m_elements,
		m_numElements
	};
}
