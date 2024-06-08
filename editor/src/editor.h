#pragma once

#include "engine/all.h"
#include "imguiAPI/imguiAPI.h"
#include "panels/scene_heirarchy.h"
#include "panels/properties.h"
#include "panels/environment_panel.h"

namespace prime {

	class Editor : public App
	{
	public:
		Editor() = default;

		void Init() override;
		void Shutdown() override;

		void Update(Timestep& timestep) override;

		AppConfig GetConfig() override
		{
			AppConfig config;
			config.maximize = true;

			return config;
		}

		void OnWindowResize(const WindowResizeEvent&);

	private:
		void SetColors();
		void Dockspace();
		void Viewport();

	private:
		Ref<Scene> m_scene;
		std::unique_ptr<ImGuiAPI> m_imguiAPI;

		Ref<Framebuffer> m_framebuffer;
		glm::vec2 m_viewportSize = glm::vec2(0.0f);

		// panels
		SceneHeirarchy m_sceneHeirarchy;
		Properties m_properties;
		EnvironmentPanel m_environmentPanel;
	};
}
