#pragma once

#include "engine/core/core.h"
#include "engine/core/GUID.h"
#include "engine/core/ref.h"

#include <entt/entt.hpp>
#include <string>

namespace prime {

	enum class SceneState
	{
		editor,
		runtime
	};

	class Entity;
	class Scene
	{
	public:
		Entity CreateEntity(const std::string& name);
		Entity CreateEntityWithGUID(GUID& gUID, const std::string& name);

		void DestroyEntity(Entity& entity);

		void SetSatte(SceneState state) { m_state = state; }
		PINLINE SceneState GetState() { return m_state; }

		void Render(SceneState state);

		static Ref<Scene> Create();

	private:
		SceneState m_state = SceneState::editor;
		entt::registry m_registry;

		friend class Entity;
	};
}
