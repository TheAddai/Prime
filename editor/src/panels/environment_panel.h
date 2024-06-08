#pragma once

#include "engine/scene/scene.h"

namespace prime {

	class EnvironmentPanel
	{
	public:
		void SetScene(Ref<Scene>& scene);
		void ImGuiRender();

	private:
		Ref<Scene> m_scene;
	};
}