#pragma once

#include "engine/scene/scene.h"
#include "engine/scene/entity.h"

namespace prime {

	class SceneHeirarchy
	{
	public:
		void SetScene(Ref<Scene>& scene);
		void ImGuiRender();

		Entity GetSelectedEntity() const { return m_selectedEntity; }
		void SetSelectedEntity(Entity entity) { m_selectedEntity = entity; }

	private:
		void DrawEntityNode(Entity entity);

	private:
		Ref<Scene> m_scene;
		Entity m_selectedEntity;

		std::vector<Entity> m_entities;
	};
}
