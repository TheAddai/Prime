#pragma once

#include "engine/core/core.h"
#include "engine/core/GUID.h"
#include <memory>
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
		static std::shared_ptr<Scene> Create();

		Entity CreateEntity(std::string& name);
		Entity CreateEntityWithGUID(GUID& gUID, std::string& name);

		void DestroyEntity(Entity& entity);

		void SetSatte(SceneState state) { m_state = state; }
		PINLINE SceneState GetState() { return m_state; }

		void Render(SceneState state);

	private:
		SceneState m_state;
		entt::registry m_registry;
		friend class Entity;
	};
}
