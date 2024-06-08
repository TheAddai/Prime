
#include "pch.h"
#include "properties.h"
#include "engine/scene/components.h"
#include "UI/vec3_control.h"
#include "UI/draw_component.h"

#include <imgui/imgui.h>

namespace prime {

	void Properties::ImGuiRender(Entity entity)
	{
		ImGui::Begin("Properties");
		m_selection = entity;

		if (m_selection)
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
}