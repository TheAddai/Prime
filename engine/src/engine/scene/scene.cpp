
#include "pch.h"
#include "scene.h"
#include "entity.h"
#include "components.h"
#include "engine/renderer/renderer2D.h"

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

	void Scene::Render()
	{
		if (m_state == SceneState::editor)
		{
			Renderer2D::Begin();
			DrawEntities();
			Renderer2D::End();
		}
	}

	void Scene::DrawEntities()
	{
		entt::basic_view sEs = m_registry.view<TransformComponent, SpriteComponent>();
		for (entt::entity sE : sEs)
		{
			auto [sT, s] = sEs.get<TransformComponent, SpriteComponent>(sE);
			Renderer2D::DrawSprite(sT, s);
		}
	}

	Ref<Scene> Scene::Create()
	{
		return CreateRef<Scene>();
	}
	
}