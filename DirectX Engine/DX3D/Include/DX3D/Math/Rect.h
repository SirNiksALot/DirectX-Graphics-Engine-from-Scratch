#pragma once
#include <DX3D/Core/Core.h>


namespace dx3d {
	class Rect {
	public:
		Rect() = default;
		Rect(i32 width, i32 height) :width(width), height(height), left(0), top(0) {};
		Rect(i32 width, i32 height , i32 top , i32 left) :width(width), height(height), left(left), top(left) {};

	public:
		i32 left{}, width{}, top{}, height{};
	};
}