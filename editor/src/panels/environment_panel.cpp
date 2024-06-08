
#include "environment_panel.h"
#include "engine/scene/entity.h"
#include "engine/scene/editor_name_component.h"

#include <imgui/imgui.h>
#include <string>

namespace prime {

	void EnvironmentPanel::SetScene(Ref<Scene>& scene)
	{
		m_scene = scene;
	}

	void EnvironmentPanel::ImGuiRender()
	{
		ImGui::Begin("Environment");

		if (m_scene.get())
		{
			std::string sceneName = "Scene: " + m_scene->GetName();
			std::string cameraName = "Scene Camera: ";
			Entity mainCamera = m_scene->GetMainCamera();
			if (mainCamera)
			{
				cameraName += mainCamera.GetComponent<EditorNameComponent>().name;
			}
			else
			{
				cameraName += "None";
			}

			ImGui::Text("%s", sceneName.c_str());
			ImGui::Text("%s", cameraName.c_str());
		}

		ImGui::End();
	}
}