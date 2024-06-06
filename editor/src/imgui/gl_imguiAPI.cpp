
#include "pch.h"
#include "gl_imguiAPI.h"
#include "engine/engine.h"
#include "engine/platform/platform.h"

#include <imgui/imgui.h>

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#ifdef PPLATFORM_WINDOWS
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // PPLATFORM_WINDOWS

namespace prime {

	void GLImGuiAPI::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

#ifdef PPLATFORM_WINDOWS
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::GetWindow().GetHandle(), true);
#endif // PPLATFORM_WINDOWS
		ImGui_ImplOpenGL3_Init("#version 400");
	}

	void GLImGuiAPI::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
#ifdef PPLATFORM_WINDOWS
		ImGui_ImplGlfw_Shutdown();
#endif // PPLATFORM_WINDOWS
		ImGui::DestroyContext();
	}

	void GLImGuiAPI::BeginRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
#ifdef PPLATFORM_WINDOWS
		ImGui_ImplGlfw_NewFrame();
#endif // PPLATFORM_WINDOWS
		ImGui::NewFrame();
	}

	void GLImGuiAPI::EndRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Engine::GetWindow();

		io.DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
#ifdef PPLATFORM_WINDOWS
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
#endif // PPLATFORM_WINDOWS
		}
	}
}
