
#include "pch.h"
#include "scene.h"
#include "entity.h"

namespace prime {

	std::shared_ptr<Scene> Scene::Create()
	{
		return std::make_shared<Scene>();
	}

	Entity Scene::CreateEntity(std::string& name)
	{
		return CreateEntityWithGUID(GUID(), name);
	}

	Entity Scene::CreateEntityWithGUID(GUID& _GUID, std::string& name)
	{
		Entity entity = Entity(m_registry.create(), this);
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity)
	{
		m_registry.destroy(entity.GetID());
	}

	void Scene::Render(SceneState state)
	{

	}
}