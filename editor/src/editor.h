#pragma once

#include "engine/all.h"
#include "imgui/imguiAPI.h"

namespace prime {

	class Editor : public App
	{
	public:
		Editor() = default;

		void Init() override;
		void Shutdown() override;

		void Update(Timestep& timestep) override;
		void OnWindowResize(const WindowResizeEvent&);

	private:
		void SetColors();

	private:
		Ref<Scene> m_scene;
		std::unique_ptr<ImGuiAPI> m_imguiAPI;

		Ref<Framebuffer> m_framebuffer;
	};
}
