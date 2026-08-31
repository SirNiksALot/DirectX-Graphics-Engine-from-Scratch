#include <DX3D/Graphics/ShaderBinary.h>
#include <d3dcompiler.h>
#include <DX3D/Graphics/GraphicsUtils.h>

dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc,const GraphicsResourceDesc& gDesc):GraphicsResource(gDesc)
{
	UINT compile_flags{};

#ifdef _DEBUG
	compile_flags |= D3DCOMPILE_DEBUG;
#endif
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	D3DCompile(
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
		&errorBlob
	);

}
