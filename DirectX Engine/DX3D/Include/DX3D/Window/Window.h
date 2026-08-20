#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>

namespace dx3d {
	class Window: public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;
	private:
		void* m_handle{};
		Rect m_size{};
	};


}