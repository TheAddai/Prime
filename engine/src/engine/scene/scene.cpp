
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
		nameC.name = name.empty() ? "Entity" + std::to_string(m_index) : name;
		m_index++;

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
		if (m_state == SceneState::editor)
		{
			RenderCommand::SetClearColor({ .2f, .2f, .2f, 1.0f });
			RenderCommand::Clear();

			DrawEntities();
		}

		else if (m_state == SceneState::runtime)
		{
			Entity cameraEntity = Entity(m_entities[m_mainCameraGUID], this);
			glm::vec4 color = cameraEntity.GetComponent<CameraComponent>().clearColor;

			RenderCommand::SetClearColor(color);
			RenderCommand::Clear();

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
		}
	}

	Entity Scene::GetMainCamera()
	{
		if (m_mainCameraGUID)
		{
			Entity entity = Entity(m_entities[m_mainCameraGUID], this);
			return entity;
		}
		return Entity();
	}

	void Scene::DrawEntities()
	{
		if (m_mainCameraGUID)
		{
			Entity cameraEntity = GetMainCamera();

			Camera& camera = cameraEntity.GetComponent<CameraComponent>().camera;
			glm::mat4 transform = GetTransformNoScale(cameraEntity.GetComponent<TransformComponent>());
			glm::mat4 viewProjectionMatrix = camera.GetProjection() * glm::inverse(transform);

			Renderer2D::Begin(viewProjectionMatrix);

			// sprites
			entt::basic_view s2dEs = m_registry.view<TransformComponent, SpriteRenderer2DComponent>();
			for (entt::entity s2dE : s2dEs)
			{
				auto [s2dT, s2d] = s2dEs.get<TransformComponent, SpriteRenderer2DComponent>(s2dE);
				Renderer2D::DrawSprite(s2dT, s2d);
			}

			// lines
			entt::basic_view l2dEs = m_registry.view<TransformComponent, Line2DComponent>();
			for (entt::entity lE : l2dEs)
			{
				auto [l2dT, l2d] = l2dEs.get<TransformComponent, Line2DComponent>(lE);
				Renderer2D::DrawLine(l2dT, l2d);
			}

			// rects
			entt::basic_view r2dEs = m_registry.view<TransformComponent, Rect2DComponent>();
			for (entt::entity rE : r2dEs)
			{
				auto [r2dT, r2d] = r2dEs.get<TransformComponent, Rect2DComponent>(rE);
				Renderer2D::DrawRect(r2dT, r2d);
			}

			Renderer2D::End();
		}
	}

	Ref<Scene> Scene::Create(const std::string& name)
	{
		return CreateRef<Scene>(name);
	}	

	Ref<Scene> Scene::Create()
	{
		return CreateRef<Scene>("Untitled");
	}
}