
#include "pch.h"
#include "engine.h"

namespace prime {

	static bool s_running = false;

	void Engine::Close()
	{
		s_running = false;
	}

	void Engine::Run(App* app)
	{
		app->Init();
		s_running = true;

		while (s_running)
		{
			app->Update();
		}

		app->Shutdown();
	}
}