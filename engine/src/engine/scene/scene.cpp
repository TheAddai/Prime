
#include "pch.h"
#include "scene.h"
#include "entity.h"
#include "components.h"
#include "engine/renderer/renderer2D.h"
#include "engine/utils/math.h"
#include "engine/renderer/render_command.h"

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

		m_entities[gUID.GetID()] = entity.GetID();
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity)
	{
		m_entities.erase(entity.GetComponent<IDComponent>().gUID.GetID());
		m_registry.destroy(entity.GetID());
	}

	void Scene::Render()
	{
		RenderCommand::Clear();

		if (m_state == SceneState::editor)
		{
			DrawEntities();
		}
	}

	void Scene::SetMainCamera(Entity entity)
	{
		if (entity.HasComponent<CameraComponent>())
		{
			m_mainCameraGUID = entity.GetComponent<IDComponent>().gUID.GetID();
			glm::vec4 color = entity.GetComponent<CameraComponent>().clearColor;
			RenderCommand::SetClearColor(color);
		}
	}

	void Scene::DrawEntities()
	{
		Entity cameraEntity = Entity(m_entities[m_mainCameraGUID], this);
		if (cameraEntity)
		{
			Camera& camera = cameraEntity.GetComponent<CameraComponent>().camera;
			glm::mat4 transform = GetTransformNoScale(cameraEntity.GetComponent<TransformComponent>());
			glm::mat4 viewProjectionMatrix = camera.GetProjection() * glm::inverse(transform);

			Renderer2D::Begin(viewProjectionMatrix);

			entt::basic_view sEs = m_registry.view<TransformComponent, SpriteComponent>();
			for (entt::entity sE : sEs)
			{
				auto [sT, s] = sEs.get<TransformComponent, SpriteComponent>(sE);
				Renderer2D::DrawSprite(sT, s);
			}

			Renderer2D::End();
		}
	}

	Ref<Scene> Scene::Create()
	{
		return CreateRef<Scene>();
	}	
}