
#include "pch.h"
#include "scene.h"
#include "entity.h"
#include "components.h"

namespace prime {

	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithGUID(GUID(), name);
	}

	Entity Scene::CreateEntityWithGUID(GUID& gUID, const std::string& name)
	{
		Entity entity = Entity(m_registry.create(), this);
		entity.AddComponent<IDComponent>(gUID);
		entity.AddComponent<TransformComponent>();
		auto& nameC = entity.AddComponent<EditorNameComponent>();
		nameC.name = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity)
	{
		m_registry.destroy(entity.GetID());
	}

	void Scene::Render(SceneState state)
	{

	}

	Ref<Scene> Scene::Create()
	{
		return CreateRef<Scene>();
	}
}