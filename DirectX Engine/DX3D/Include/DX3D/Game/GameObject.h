#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Identifiable.h>
#include <unordered_map>
#include <DX3D/Game/Component.h>

namespace dx3d {
	class GameObject : public Identifiable
	{
		dx3d_typeid(GameObject);
	public:
		explicit GameObject(const GameObjectDesc& desc);

		template<typename T>
		T* createOrGetComponent() requires isRegistered<Component, T>
		{
			auto c = getComponent<T>();
			if (c) return c;

			UniquePtr<Component>  cp = std::make_unique<T>(ComponentDesc{
				{m_logger},
				*this,
				m_world
				});
			return static_cast<T*>(createComponentInternal(cp));
		}

		template<typename T>
		T* getComponent() requires isRegistered<Component, T>
		{
			return static_cast<T*>(getComponentInternal(T::GetTypeId()));
		}

	protected:
		virtual void onCreate() {};
		virtual void onUpdate(f32 deltaTime) {};

	private:
		size_t getWorldIndex() const noexcept;
		void setWorldIndex(size_t index) noexcept;

		Component* createComponentInternal(UniquePtr<Component>& component);
		Component* getComponentInternal(size_t id);

	private:
		World& m_world;
		std::unordered_map<size_t, UniquePtr<Component>> m_components{};
		
		friend class World;

	};
}

