#pragma once
#include <DX3D/Core/Common.h>
#include <d3d11.h>
#include <bit>

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

		inline DXGI_FORMAT GetDXGIFormatFromMask(D3D_REGISTER_COMPONENT_TYPE type, UINT mask) {
			// "mask" is a bit mask to represent which components are active. For example:
			// if x,y,z are active and w not active ==> 1,1,1,0
			// if all 4 are active them ==> 1,1,1,1

			auto componentCount = std::popcount(mask); // counts number of 1s in mask
			if (componentCount < 1) return DXGI_FORMAT_UNKNOWN;


			constexpr DXGI_FORMAT formatTable[1][4] = {
				{
					DXGI_FORMAT_R32_FLOAT,
					DXGI_FORMAT_R32G32_FLOAT,
					DXGI_FORMAT_R32G32B32_FLOAT,
					DXGI_FORMAT_R32G32B32A32_FLOAT,
				}
			};


			auto typeIndex = 0u;
			switch (type) {
				case D3D_REGISTER_COMPONENT_FLOAT32: typeIndex = 0u; break;
				default: return DXGI_FORMAT_UNKNOWN;
			}
			return formatTable[typeIndex][componentCount - 1];
		}
	}
}