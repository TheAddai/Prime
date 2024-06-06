
#include "editor.h"

namespace prime {

	void Editor::Init()
	{
		RenderCommand::SetClearColor({ .2f, .2f, .2f, 1.0f });
		Dispatcher::Get().sink<WindowResizeEvent>().connect<&Editor::OnWindowResize>(this);

		m_scene = Scene::Create();
		Entity player = m_scene->CreateEntity("Player");
		player.AddComponent<SpriteComponent>();
	}

	void Editor::Shutdown()
	{

	}

	void Editor::Update(Timestep& timestep)
	{
		RenderCommand::Clear();

		m_scene->SetState(SceneState::editor);
		m_scene->Render();
	}
	
	void Editor::OnWindowResize(const WindowResizeEvent& e)
	{
		RenderCommand::SetViewport(e.GetWidth(), e.GetHeight());
	}
}