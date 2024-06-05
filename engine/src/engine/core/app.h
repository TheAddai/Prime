#pragma once

#include <string>

namespace prime {

	struct AppConfig
	{
		uint32_t width = 640, height = 480;
		bool fullscreen = false;
		std::string title = "Prime Application";
	};

	class App
	{
	public:
		virtual void Init() {}
		virtual void Shutdown() {}

		virtual void Update() {}
		virtual AppConfig GetConfig() { return AppConfig(); }
	};

	App* CreateApplication();
}
