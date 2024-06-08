#pragma once

#include "engine/all.h"
#include "imguiAPI/imguiAPI.h"
#include "panels/scene_heirarchy.h"
#include "panels/properties.h"
#include "panels/environment_panel.h"
#include "panels/content_browser.h"

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
		void ResizeViewport();
		void MenuBar();

	private:
		std::unique_ptr<ImGuiAPI> m_imguiAPI;

		Ref<Framebuffer> m_framebuffer;
		glm::vec2 m_viewportSize = glm::vec2(0.0f);

		bool m_viewportFocused = false, m_viewportHovered = false;
		glm::vec2 m_viewportBounds[2]{};

		Ref<Project> m_project;

		// panels
		SceneHeirarchy m_sceneHeirarchy;
		Properties m_properties;
		EnvironmentPanel m_environmentPanel;
		ContentBrowser m_contentBrowser;
	};
}
