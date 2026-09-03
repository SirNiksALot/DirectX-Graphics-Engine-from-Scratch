#pragma once
#include <DX3D/Core/Logger.h>
#include <d3d11.h>

namespace dx3d {

	namespace GraphicsLogUtils {
		inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorBlob) {

			auto errorMessage = errorBlob ? static_cast<const char*>(errorBlob->GetBufferPointer()) : nullptr;

			if (FAILED(hr)) {
				if (errorMessage) {
					DX3DLogThrow(logger, std::runtime_error, dx3d::Logger::LogLevel::Error, errorMessage);
				}
				else {
					DX3DLogThrow(logger, std::runtime_error, dx3d::Logger::LogLevel::Error, "Shader compilation failed.");

				}
			}

			if (errorMessage) { // Sometimes error messages issue warnings but th compilation succeeds.
				DX3DLog(logger, dx3d::Logger::LogLevel::Warning, errorMessage);
			}

		}
	}
}

#define DX3DGraphicsLogThrowOnFail(hr,message)\
{\
auto res = (hr); \
if (FAILED(res))\
	DX3DLogThrow(getLogger(),std::runtime_error,dx3d::Logger::LogLevel::Error,message);\
}

#define DX3DGraphicsCheckShaderCompile(hr,errroBlob)\
{\
auto res = (hr);\
dx3d::GraphicsLogUtils::CheckShaderCompile(getLogger(),res,errorBlob);\
}