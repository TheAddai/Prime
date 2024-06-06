
#include "editor.h"

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

		Entity mainCamera = m_scene->CreateEntity("MainCamera");
		mainCamera.AddComponent<CameraComponent>();
		m_scene->SetMainCamera(mainCamera);
	}

	void Editor::Shutdown()
	{

	}

	void Editor::Update(Timestep& timestep)
	{
		m_scene->Render();
	}
	
	void Editor::OnWindowResize(const WindowResizeEvent& e)
	{
		m_scene->ViewportResize(e.GetWidth(), e.GetHeight());
		RenderCommand::SetViewport(e.GetWidth(), e.GetHeight());
	}
}