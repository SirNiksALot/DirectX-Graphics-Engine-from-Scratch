#pragma once
#include <DX3D/Core/Logger.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Math/Rect.h>


namespace dx3d{
	struct BaseDesc {
		Logger& logger;
	};

	struct WindowDesc {
		BaseDesc base;
		Rect size{};
	};

	struct DisplayDesc {
		WindowDesc window;
		GraphicsDevice& graphicsDevice;
	};

	struct GraphicsEngineDesc {
		BaseDesc base;
	};

	struct GraphicsDeviceDesc {
		BaseDesc base;
	};
	
	struct GameDesc {
		Rect windowSize{ 1280,720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};

	struct SwapChainDesc {
		void* winHandle{};
		Rect winSize{};
	};

	enum ShaderType {
		VertexShader = 0,
		PixelShader
	};

	struct ShaderBinaryData {
		const void* data{};
		size_t dataSize{};
	};

	struct ShaderCompileDesc {
		const char* shaderSourceName{};
		const void* shaderSourceCode{};
		size_t shaderSourceCodeSize{};
		const char* shaderEntryPoint{}; //name of the entrypoint function in the shadercode
		ShaderType shaderType{};
	};

	struct GraphicsPipelineStateDesc {
		const ShaderBinary& vs;
		const ShaderBinary& ps;
	};

	struct VertexBufferDesc {
		const void* vertexList{};
		ui32 vertexListSize{}; // number of vertices
		ui32 vertexSize{}; // size of single vertex in bytes 
	};
}