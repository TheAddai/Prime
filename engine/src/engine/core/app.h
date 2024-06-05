#pragma once

#include "engine/renderer/renderer.h"
#include "timestep.h"

#include <string>

namespace prime {

	enum AppType
	{
		appType2D,
		appType3D
	};

	struct AppConfig
	{
		uint32_t width = 640, height = 480;
		bool maximize = false, vSync = true;
		std::string title = "Prime Application";
		GraphicsAPI graphicsAPI = GraphicsAPI::graphicsAPIOpenGL;
		AppType type = AppType::appType2D;
	};

	class App
	{
	public:
		virtual void Init() {}
		virtual void Shutdown() {}

		virtual void Update(Timestep& timestep) {}
		virtual AppConfig GetConfig() { return AppConfig(); }
	};

	App* CreateApplication();
}
