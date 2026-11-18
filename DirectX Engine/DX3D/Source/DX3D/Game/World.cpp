#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Game/Component.h>

dx3d::World::World(const WorldDesc& desc):Base(desc.base)
{
}

void dx3d::World::update(f32 deltaTime)
{

	if (m_events.size()) {
		std::swap(m_events, m_eventsSwapBuffer);
		std::swap(m_pendingObjects, m_pendingObjectsSwapBuffer);

		for (auto& e : m_eventsSwapBuffer) {
			auto objectTypeId = e.object->getTypeId();
			auto pendingObjIndex = e.pendingObjectIndex;

			if (e.eventType == EventType::Create) {
				
				auto& obj = m_pendingObjectsSwapBuffer[pendingObjIndex];
				auto ptr = obj.get();


				m_objects[objectTypeId].push_back(std::move(obj)); //std::move because this is the way of "transferring ownership" of unique pointers


				ptr->onCreate();

			}
		}

		m_eventsSwapBuffer.clear();
		m_pendingObjectsSwapBuffer.clear();

	}


	for (auto&& [typeId, objects] : m_objects) {
		for (auto& object : objects) {
			object->onUpdate(deltaTime);
		}
	}

	for (auto& comp : m_dirtyTransforms) {
		comp->updateWorldMatrix();
	}

	m_dirtyTransforms.clear();
}

dx3d::GameObject* dx3d::World::createGameObjectInternal(UniquePtr<GameObject>& object)
{
	if (!object) return{};
	
	auto ptr = object.get();
	auto index = m_pendingObjects.size();


	m_pendingObjects.push_back(std::move(object));
	m_events.push_back({ ptr,index,EventType::Create });

	return ptr;

}

void dx3d::World::addComponentInternal(Component& component)
{
	auto typeId = component.getTypeId();
	m_components[typeId].push_back(&component);
}

void dx3d::World::addDirtyTransformInternal(TransformComponent& component)
{
	m_dirtyTransforms.push_back(&component);
}
