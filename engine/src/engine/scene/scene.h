#pragma once

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
		Entity CreateEntityWithGUID(GUID& _GUID, std::string& name);

		void DestroyEntity(Entity& entity);

		void Render(SceneState state);

	private:
		entt::registry m_registry;
		friend class Entity;
	};
}
