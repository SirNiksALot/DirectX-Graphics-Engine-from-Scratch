#pragma once
#include <DX3D/Core/Identifiable.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>


namespace dx3d {
	class Component : public Identifiable
	{
		dx3d_typeid(Component)


	public:
		explicit Component(const ComponentDesc& desc);
		GameObject& getGameObject() noexcept;

	protected:
		GameObject& m_object;
		World& m_world;
	};

}
