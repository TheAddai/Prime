
#include "pch.h"
#include "engine.h"
#include "core/logger.h"

namespace prime {

	static bool s_running = false;

	void Engine::Close()
	{
		s_running = false;
	}

	void Engine::Run(App* app)
	{
		Logger::Init();
		app->Init();
		s_running = true;

		while (s_running)
		{
			app->Update();
		}

		app->Shutdown();
		Logger::Shutdown();
	}
}