
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

	void Scene::ViewportResize(uint32_t width, uint32_t height)
	{
		if (m_viewport.x == width && m_viewport.y == height) { return; }
		if (m_viewport.x < 0 && m_viewport.y < 0) { return; }

		m_viewport.x = width;
		m_viewport.y = height;

		auto view = m_registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.fixedAspectRatio)
				cameraComponent.camera.SetViewport(width, height);
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

			// sprites
			entt::basic_view sEs = m_registry.view<TransformComponent, SpriteComponent>();
			for (entt::entity sE : sEs)
			{
				auto [sT, s] = sEs.get<TransformComponent, SpriteComponent>(sE);
				Renderer2D::DrawSprite(sT, s);
			}

			// lines
			entt::basic_view lEs = m_registry.view<TransformComponent, LineComponent>();
			for (entt::entity lE : lEs)
			{
				auto [lT, l] = lEs.get<TransformComponent, LineComponent>(lE);
				Renderer2D::DrawLine(lT, l);
			}

			// rects
			entt::basic_view rEs = m_registry.view<TransformComponent, RectComponent>();
			for (entt::entity rE : rEs)
			{
				auto [rT, r] = rEs.get<TransformComponent, RectComponent>(rE);
				Renderer2D::DrawRect(rT, r);
			}

			Renderer2D::End();
		}
	}

	Ref<Scene> Scene::Create()
	{
		return CreateRef<Scene>();
	}	
}