
#include "editor.h"

namespace prime {

	void Editor::Init()
	{
		RenderCommand::SetClearColor({ .2f, .2f, .2f, 1.0f });

		m_scene = Scene::Create();

		Entity player = m_scene->CreateEntity("Player");
	}

	void Editor::Shutdown()
	{

	}

	void Editor::Update(Timestep& timestep)
	{
		RenderCommand::Clear();
	}
}