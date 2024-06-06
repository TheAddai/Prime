
#include "pch.h"
#include "engine.h"
#include "events/all.h"
#include "core/all.h"
#include "renderer/all.h"

namespace prime {

	static bool s_running = false;
	static Window s_window;
	static Timestep s_timestep;

	static void OnWindowClose(const WindowCloseEvent&)
	{
		Engine::Close();
	}

	void Engine::Close()
	{
		s_running = false;
	}

	void Engine::Run(App* app)
	{
		Logger::Init();

		// window
		WindowConfig windowConfig;
		AppConfig appConfig = app->GetConfig();
		windowConfig.title = appConfig.title;
		windowConfig.width = appConfig.width;
		windowConfig.height = appConfig.height;
		windowConfig.maximize = appConfig.maximize;
		windowConfig.vSync = appConfig.vSync;
		s_window.Init(windowConfig);

		// context
		Renderer::SetGraphicsAPI(appConfig.graphicsAPI);
		RenderCommand::Init();

		// renderers
		if (appConfig.type == appType2D) { Renderer2D::Init(); }
		else if (appConfig.type == appType3D) { Renderer::Init(); Renderer2D::Init(); }

		app->Init();

		// subscribe to events
		Dispatcher::Get().sink<WindowCloseEvent>().connect<&OnWindowClose>();
		s_running = true;

		while (s_running)
		{
			s_timestep.Tick();
			s_window.PollEvents();

			Dispatcher::Get().update();
			app->Update(s_timestep);
			s_window.SwapBuffers();
		}

		app->Shutdown();
		Dispatcher::Get().clear();

		if (appConfig.type == appType2D) { Renderer2D::Shutdown(); }
		else if (appConfig.type == appType3D) { Renderer::Shutdown(); Renderer2D::Shutdown(); }

		s_window.Shutdown();
		Logger::Shutdown();
	}
}