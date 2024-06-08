
#include "pch.h"
#include "scene_heirarchy.h"
#include "engine/scene/components.h"

#include <imgui/imgui.h>

namespace prime {

	void SceneHeirarchy::SetScene(Ref<Scene>& scene)
	{
		m_scene = scene;
		m_selectedEntity = {};
	}

	void SceneHeirarchy::ImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		if (m_scene.get())
		{
			// create entities
			m_entities.clear();
			entt::basic_view entities = m_scene->GetEntities<TransformComponent>();
			for (entt::entity entityID : entities)
			{
				Entity entity{ entityID, m_scene.get() };
				m_entities.push_back(entity);
			}

			// render entities
			for (auto iterator = m_entities.rbegin(); iterator != m_entities.rend(); ++iterator)
			{
				DrawEntityNode((*iterator));
			}

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_selectedEntity = {};

			// Right-click on blank space
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create Entity"))
					m_scene->CreateEntity("");

				ImGui::EndPopup();
			}
		}

		ImGui::End();
	}

	void SceneHeirarchy::DrawEntityNode(Entity entity)
	{
		auto& name = entity.GetComponent<EditorNameComponent>().name;

		ImGuiTreeNodeFlags flags = ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_selectedEntity = entity;
		}

		bool entityDeleted = false;
		bool selectedCamera = false;
		if (ImGui::BeginPopupContextItem(name.c_str()))
		{
			if (ImGui::MenuItem("Delete Entity")) { entityDeleted = true; }

			if (entity.HasComponent<CameraComponent>())
			{
				if (ImGui::MenuItem("Set SceneCamera")) { selectedCamera = true; }
			}

			ImGui::EndPopup();
		}

		if (opened)
		{
			// add child nodes here
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_scene->DestroyEntity(entity);
			if (m_selectedEntity == entity)
				m_selectedEntity = {};
		}

		if (selectedCamera)
		{
			m_scene->SetMainCamera(entity);
		}
	}
}