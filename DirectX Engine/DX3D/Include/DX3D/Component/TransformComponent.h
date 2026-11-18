#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Mat4x4.h>

namespace dx3d {
	class TransformComponent final : public Component
	{
		dx3d_typeid(TransformComponent)

	public:
		explicit TransformComponent(const ComponentDesc& desc);

		void setPosition(const Vec3& position);
		Vec3 getPosition() const noexcept;


		void setRotation(const Vec3& rotation);
		Vec3 getRotation() const noexcept;


		void setScale(const Vec3& scale);
		Vec3 getScale() const noexcept;

		void updateWorldMatrix() noexcept;

	private:
		void markAsDirty();

	private:
		Vec3 m_position{ 0,0,0 };
		Vec3 m_rotation{ 0,0,0 };
		Vec3 m_scale{ 1,1,1 };

		Mat4x4 m_worldMat{};

		bool m_dirty{}; // Dirty flag ( to denote if object underwent changes compared to previous frame )

	};
}

