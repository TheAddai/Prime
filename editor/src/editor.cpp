
#include "editor.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace prime {

	static const char* GetStringFromType(AppType type)
	{
		switch (type)
		{
		case prime::appType2D: return "2D"; break;
		case prime::appType3D: return "3D"; break;
			break;
		}
		return "";
	}

	void Editor::Init()
	{
		Dispatcher::Get().sink<WindowResizeEvent>().connect<&Editor::OnWindowResize>(this);

		// imgui
		m_imguiAPI = ImGuiAPI::Create();
		m_imguiAPI->Init();
		SetColors();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		float fontSize = 14.0f;
		io.Fonts->AddFontFromFileTTF("assets/fonts/roboto_bold.ttf", fontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/roboto_regular.ttf", fontSize);

		// framebuffer
		FramebufferConfig fbConfig;
		fbConfig.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::depth };
		fbConfig.width = 1280;
		fbConfig.height = 720;
		m_framebuffer = Framebuffer::Create(fbConfig);

		m_projectTemplate = Texture2D::Create(TextureConfig());
	}

	void Editor::Shutdown()
	{
		m_imguiAPI->Shutdown();
	}

	void Editor::Update(Timestep& timestep)
	{
		ResizeViewport();

		if (m_project.get())
		{
			m_framebuffer->Bind();
			m_project->GetActiveScene()->Render();
			m_framebuffer->Unbind();
		}

		m_imguiAPI->BeginRender();

		Dockspace();
		m_sceneHeirarchy.ImGuiRender();
		m_properties.ImGuiRender(m_sceneHeirarchy.GetSelectedEntity());
		m_environmentPanel.ImGuiRender();
		m_contentBrowser.ImGuiRender();
		Viewport();

		NewProject();

		m_imguiAPI->EndRender();
	}
	
	void Editor::OnWindowResize(const WindowResizeEvent& e)
	{
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
	
	void Editor::Dockspace()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		MenuBar();
		ImGui::End();
	}

	void Editor::Viewport()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_viewportFocused = ImGui::IsWindowFocused();
		m_viewportHovered = ImGui::IsWindowHovered();

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_framebuffer->GetTextureID();
		ImGui::Image((ImTextureID)textureID, { m_viewportSize.x, m_viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// accept draw
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				// open scene
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	void Editor::ResizeViewport()
	{
		if (m_project.get())
		{
			m_project->GetActiveScene()->ViewportResize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
		}

		glm::vec2 size = glm::vec2(0.0f);
		size.x = (float)m_framebuffer->GetWidth();
		size.y = (float)m_framebuffer->GetHeight();

		if (m_viewportSize.x > 0.0f && m_viewportSize.y > 0.0f &&
			(size.x != m_viewportSize.x || size.y != m_viewportSize.y))
		{
			m_framebuffer->Resize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
		}
	}

	void Editor::MenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					Engine::Close();
				}

				ImGui::Separator();

				if (ImGui::MenuItem("New Project...", "Ctrl+Shift+N"))
				{
					m_newProject = true;
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

	void Editor::NewProject()
	{
		if (m_newProject)
		{
			ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse;
			flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking;

			ImGui::Begin("Create Project", NULL, flags);
			ImVec2 buttonSize = { 100.0f, 30.0f };
			ImVec2 windowSize = { 640.0f, 480.0f };
			ImVec2 pos = { 0.0f, 0.0f };
			float offset = 100.0f;
			pos.x = windowSize.x / 2.0f - buttonSize.x / 2.0f;
			pos.y = windowSize.y / 2.0f - buttonSize.y / 2.0f;
			ImGui::SetWindowSize("Create Project", windowSize);

			// template image
			ImGui::SetCursorPos({ 120.0f, 40.0f });
			uint64_t textureID = m_projectTemplate->GetHandle();
			ImGui::Image((ImTextureID)textureID, { 400.0f, 200.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			// project types
			ImGui::SetCursorPos({ pos.x - 200.0f, pos.y + 40 });
			ImGui::Text("%s", "Project Type: ");

			ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
			ImGui::SameLine(0.0f, 15.0f);
			const char* projectTypeStrings[] = { "2D", "3D" };
			const char* currentProjectTypeString = GetStringFromType(m_config.type);
			if (ImGui::BeginCombo("##ProjectTypes", currentProjectTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectTypeString == projectTypeStrings[i];
					if (ImGui::Selectable(projectTypeStrings[i], isSelected))
					{
						currentProjectTypeString = projectTypeStrings[i];
						m_config.type = (AppType)i;
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			// project name
			ImGui::SetCursorPos({ pos.x - 200.0f, pos.y + 70 });
			ImGui::Text("%s", "Project Name: ");

			char nameBuffer[50];
			memset(nameBuffer, 0, sizeof(nameBuffer));
			strncpy_s(nameBuffer, sizeof(nameBuffer), m_config.name.c_str(), sizeof(nameBuffer));

			ImGui::SameLine(0.0f);
			if (ImGui::InputText("##ProjectName", nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_AutoSelectAll))
			{
				m_config.name = std::string(nameBuffer);
			}

			// project path
			ImGui::SetCursorPos({ pos.x - 200.0f, pos.y + 100 });
			ImGui::Text("%s", "Project Path: ");

			char pathBuffer[256];
			memset(pathBuffer, 0, sizeof(pathBuffer));
			strncpy_s(pathBuffer, sizeof(pathBuffer), m_config.path.string().c_str(), sizeof(pathBuffer));

			ImGui::SameLine(0.0f, 15.0f);
			if (ImGui::InputText("##ProjectPath", pathBuffer, sizeof(pathBuffer), ImGuiInputTextFlags_AutoSelectAll))
			{
				m_config.path = std::string(pathBuffer);
			}

			ImGui::PopItemWidth();

			// path button
			ImGui::SetCursorPos({ pos.x + 307.0f, pos.y + 100.0f });
			if (ImGui::Button("...", {20.0f, 20.0f}))
			{
				
			}


			// create button
			ImGui::SetCursorPos({ pos.x - offset, pos.y + 160.0f });
			if (ImGui::Button("Create", buttonSize))
			{

			}

			// exit button
			ImGui::SetCursorPos({ pos.x + offset, pos.y + 160.0f });
			if (ImGui::Button("Exit", buttonSize))
			{
				m_newProject = false;
			}

			ImGui::End();
		}
	}
}