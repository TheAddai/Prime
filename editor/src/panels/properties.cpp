
#include "pch.h"
#include "properties.h"
#include "engine/scene/components.h"
#include "UI/vec3_control.h"
#include "UI/draw_component.h"
#include "UI/vec2_control.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace prime {

	template<typename T>
	void DisplayAddComponentEntry(Entity entity, const std::string& entryName)
	{
		if (!entity.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				entity.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

	void Properties::ImGuiRender(Entity entity)
	{
		ImGui::Begin("Properties");
		m_selection = entity;

		if (m_selection)
		{
			DrawComponents(m_selection);
			DrawAddComponentButton();
		}

		ImGui::End();
	}

	void Properties::DrawNameComponent()
	{
		auto& name = m_selection.GetComponent<EditorNameComponent>().name;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strncpy_s(buffer, sizeof(buffer), name.c_str(), sizeof(buffer));

		if (ImGui::InputText("##Tag", buffer, sizeof(buffer), ImGuiInputTextFlags_AutoSelectAll))
		{
			name = std::string(buffer);
		}
	}
	
	void Properties::DrawAddComponentButton()
	{
		float width = ImGui::GetContentRegionAvailWidth();
		ImGui::SetCursorPos({ width / 2.0f - (100.0f / 2.0f), ImGui::GetCursorPosY() + 30.0f });

		if (ImGui::Button("Add Component", { 100.0f, 20.0f }))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			DisplayAddComponentEntry<SpriteRenderer2DComponent>(m_selection, "Sprite Renderer2D");
			DisplayAddComponentEntry<CameraComponent>(m_selection, "Camera");
			DisplayAddComponentEntry<Line2DComponent>(m_selection, "Line2D");
			DisplayAddComponentEntry<Rect2DComponent>(m_selection, "Rect2D");
			ImGui::EndPopup();
		}
	}
	
	void Properties::DrawComponents(Entity entity)
	{
		DrawNameComponent();

		DrawComponent<TransformComponent>("Transform", entity, false, [](auto& component)
			{
				float columnWidth = 60.0f;
				DrawVec3Control("Position", component.position, 0.0f, columnWidth);
				glm::vec3 rotation = glm::degrees(component.rotation);
				DrawVec3Control("Rotation", rotation, 0.0f, columnWidth);
				component.rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.scale, 1.0f, columnWidth);
			});

		DrawComponent<SpriteRenderer2DComponent>("SpriteRenderer2D", entity, true, [](auto& component)
			{
				ImGui::ColorPicker4("##SpriteColor", glm::value_ptr(component.color));
			});

		DrawComponent<CameraComponent>("Camera", entity, true, [](auto& component)
			{
				ImGui::ColorPicker4("##CameraColor", glm::value_ptr(component.clearColor));
				Camera& camera = component.camera;

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == ProjectionType::perspective)
				{
					float perspectiveFov = glm::degrees(camera.GetPerspectiveFOV());
					if (ImGui::DragFloat("FOV", &perspectiveFov))
						camera.SetPerspectiveFOV(glm::radians(perspectiveFov));

					float perspectiveNear = camera.GetPerspectiveNear();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNear(perspectiveNear);

					float perspectiveFar = camera.GetPerspectiveFar();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFar(perspectiveFar);
				}

				if (camera.GetProjectionType() == ProjectionType::orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNear();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNear(orthoNear);

					float orthoFar = camera.GetOrthographicFar();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFar(orthoFar);

					ImGui::Checkbox("Fixed Aspect Ratio", &component.fixedAspectRatio);
				}
			});

		DrawComponent<Line2DComponent>("Line2D", entity, true, [](auto& component)
			{
				DrawVec2Control("EndPoint", component.endPosition, 1.0f, 70.0f);
				ImGui::NewLine();
				ImGui::ColorPicker4("##LineColor", glm::value_ptr(component.color));
			});

		DrawComponent<Rect2DComponent>("Rect2D", entity, true, [](auto& component)
			{
				ImGui::ColorPicker4("##RectColor", glm::value_ptr(component.color));
			});
	}
}