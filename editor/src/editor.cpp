
#include "editor.h"

#include <imgui/imgui.h>

namespace prime {

	void Editor::Init()
	{
		RenderCommand::SetClearColor({ .2f, .2f, .2f, 1.0f });
		Dispatcher::Get().sink<WindowResizeEvent>().connect<&Editor::OnWindowResize>(this);

		m_scene = Scene::Create();
		Entity player = m_scene->CreateEntity("Player");
		player.AddComponent<SpriteComponent>().color = { 0.0f,1.0f,0.0f,1.0f };

		Entity line = m_scene->CreateEntity("Line");
		line.AddComponent<LineComponent>();

		Entity rect = m_scene->CreateEntity("Rect");
		rect.AddComponent<RectComponent>();

		Entity mainCamera = m_scene->CreateEntity("MainCamera");
		mainCamera.AddComponent<CameraComponent>();
		m_scene->SetMainCamera(mainCamera);

		// imgui
		m_imguiAPI = ImGuiAPI::Create();
		m_imguiAPI->Init();
		SetColors();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		float fontSize = 14.0f;
		io.Fonts->AddFontFromFileTTF("assets/fonts/roboto_bold.ttf", fontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/roboto_regular.ttf", fontSize);
	}

	void Editor::Shutdown()
	{
		m_imguiAPI->Shutdown();
	}

	void Editor::Update(Timestep& timestep)
	{
		m_scene->Render();

		m_imguiAPI->BeginRender();
		bool show = true;
		ImGui::ShowDemoWindow(&show);
		m_imguiAPI->EndRender();
	}
	
	void Editor::OnWindowResize(const WindowResizeEvent& e)
	{
		m_scene->ViewportResize(e.GetWidth(), e.GetHeight());
		RenderCommand::SetViewport(e.GetWidth(), e.GetHeight());
	}

	void Editor::SetColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}