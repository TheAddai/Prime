#pragma once

#include "engine/core/core.h"
#include "engine/core/GUID.h"
#include "engine/core/ref.h"

#include <entt/entt.hpp>
#include <string>
#include <map>
#include <glm/glm.hpp>

namespace prime {

	enum class SceneState
	{
		editor,
		runtime
	};

	class Entity;
	class Project;
	class Scene
	{
	public:
		Scene() = default;
		Scene(Project* project, const std::string& name)
			: m_project(project), m_name(name) { }

		Entity CreateEntity(const std::string& name);
		Entity CreateEntityWithGUID(GUID& gUID, const std::string& name);

		void DestroyEntity(Entity& entity);

		void SetState(SceneState state) { m_state = state; }
		PINLINE SceneState GetState() { return m_state; }

		void Render();

		void ViewportResize(uint32_t width, uint32_t height);

		void SetMainCamera(Entity entity);
		Entity GetMainCamera();

		template<typename T>
		auto GetEntities()
		{
			return m_registry.view<T>();
		}

		std::string GetName() const { return m_name; }

		static Ref<Scene> Create(Project*, const std::string& name);
		static Ref<Scene> Create(Project* project);

	private:
		void DrawEntities();

	private:
		SceneState m_state = SceneState::editor;
		entt::registry m_registry;

		std::string m_name = "";
		uint32_t m_index = 0;
		std::map<uint64_t, entt::entity> m_entities;
		uint64_t m_mainCameraGUID = 0;
		glm::u32vec2 m_viewport = glm::u32vec2(0);

		Project* m_project = nullptr;

		friend class Entity;
	};
}
