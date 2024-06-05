
#include "pch.h"
#include "engine.h"
#include "core/assert.h"
#include "events/dispatcher.h"
#include "events/window_events.h"
#include "core/window.h"
#include "renderer/all.h"

namespace prime {

	static bool s_running = false;
	static Window s_window;
	static std::unique_ptr<Context> s_context;

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
		windowConfig.fullscreen = appConfig.fullscreen;
		s_window.Init(windowConfig);

		// context
		Renderer::SetGraphicsAPI(appConfig.graphicsAPI);
		s_context = Context::Create();
		s_context->Init(s_window);

		app->Init();

		// subscribe to events
		Dispatcher::Get().sink<WindowCloseEvent>().connect<&OnWindowClose>();

		s_running = true;

		while (s_running)
		{
			Dispatcher::Get().update();
			app->Update();
			s_window.Update();

			s_context->SwapBuffers();
		}

		app->Shutdown();
		Dispatcher::Get().clear();
		s_context->Shutdown();
		s_window.Shutdown();
		Logger::Shutdown();
	}
}