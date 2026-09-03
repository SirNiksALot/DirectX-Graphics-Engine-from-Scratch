#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class ShaderBinary final : public GraphicsResource
	{
	public:
		ShaderBinary(const ShaderCompileDesc& desc,const GraphicsResourceDesc& gDesc);

		ShaderBinaryData getData() const noexcept;

		ShaderType getType() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3DBlob> m_blob{}; 
		ShaderType m_type{};
	};

}
