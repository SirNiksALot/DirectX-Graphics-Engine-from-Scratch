#include <DX3D/Graphics/ShaderBinary.h>
#include <d3dcompiler.h>
#include <DX3D/Graphics/GraphicsUtils.h>

dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc,const GraphicsResourceDesc& gDesc)
	:GraphicsResource(gDesc),m_type(desc.shaderType)
{

	if (!desc.shaderSourceName) DX3DLogThrowInvalidArg("No shader source name provided.");
	if (!desc.shaderSourceCode) DX3DLogThrowInvalidArg("No shader source code provided.");
	if (!desc.shaderSourceCodeSize) DX3DLogThrowInvalidArg("No shader source code size provided.");
	if (!desc.shaderEntryPoint) DX3DLogThrowInvalidArg("No shader entry point provided.");

	UINT compile_flags{};

#ifdef _DEBUG
	compile_flags |= D3DCOMPILE_DEBUG;
#endif
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{};

	DX3DGraphicsCheckShaderCompile(D3DCompile(
		desc.shaderSourceCode,
		desc.shaderSourceCodeSize,
		desc.shaderSourceName,
		nullptr,
		nullptr,
		desc.shaderEntryPoint,
		dx3d::GraphicsUtils::GetShaderModelTarget(desc.shaderType),
		compile_flags,
		0,
		&m_blob,
		&errorBlob),errorBlob.Get());

}

dx3d::ShaderBinaryData dx3d::ShaderBinary::getData() const noexcept
{
	return {
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize()
	};
}

dx3d::ShaderType dx3d::ShaderBinary::getType() const noexcept
{
	return m_type;
}
