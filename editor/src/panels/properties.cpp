
#include "pch.h"
#include "properties.h"

#include <imgui/imgui.h>

namespace prime {

	void Properties::ImGuiRender(Entity entity)
	{
		ImGui::Begin("Properties");
		m_selection = entity;

		if (m_selection)
		{
			DrawNameComponent();
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