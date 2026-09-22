#pragma once
#include <stdexcept>
#include <memory>

#define dx3d_disable_copy_and_move(className)\
		protected:\
			className(const className&) = delete;\
			className(className&&) = delete;\
			className& operator = (const className&) = delete;\
			className& operator = (className&&) = delete;

namespace dx3d {
	class Base;
	class Window;
	class Game;
	class GraphicsDevice;
	class GraphicsEngine;
	class Logger;
	class SwapChain;
	class Display;
	class DeviceContext;
	class ShaderBinary;
	class GraphicsPipelineState;
	class VertexShaderSignature;
	class VertexBuffer;
	class ConstantBuffer;

	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;


	template <typename T> using RefPtr = std::shared_ptr<T>;
	template <typename T> using UniquePtr = std::unique_ptr<T>;



}