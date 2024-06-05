#pragma once

#include "core.h"

#include <string>

namespace prime {

	using WindowHandle = void*;

	struct WindowConfig
	{
		uint32_t width = 0, height = 0;
		bool fullscreen = false;
		std::string title = "";
	};

	class Window
	{
	public:
		void Init(const WindowConfig& windowConfig);
		void Shutdown();

		void Update();

		PINLINE uint32_t GetWidth() { return m_config.width; }
		PINLINE uint32_t GetHeight() { return m_config.height; }

		PINLINE bool IsFullscreen() { return m_config.fullscreen; }
		PINLINE WindowHandle GetHandle() { return m_handle; }

	private:
		WindowHandle m_handle = nullptr;
		WindowConfig m_config;
	};
}
