#pragma once
#include <DX3D/Core/Logger.h>
#include <d3d11.h>

namespace dx3d {

	inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorBlob) {
		auto errorMessage = errorBlob ? static_cast<const char*>(errorBlob->GetBufferPointer()) : nullptr;

		if (FAILED(hr)) {
			if (errorMessage) {
				DX3DLogErrorAndThrowException(errorMessage)
			}
		}
	}
}

#define DX3DGraphicsLogThrowOnFail(hr,message)\
	{\
	auto res = (hr); \
	if (FAILED(res))\
		DX3DLogErrorAndThrowException(message);\
	}\
