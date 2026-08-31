#pragma once
#include <DX3D/Core/Common.h>

namespace dx3d {
	namespace GraphicsUtils {
		// inline funcs in namespaces prevent linker errors for utilities 
		inline const char* GetShaderModelTarget(ShaderType type) {
			switch (type) {
			case ShaderType::VertexShader: return "vs_5_0";
			case ShaderType::PixelShader: return "ps_5_0";
			default: return "";
			}
		}
	}
}