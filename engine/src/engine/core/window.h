#pragma once

#include "core.h"
#include "engine/renderer/context.h"

#include <string>

namespace prime {

	struct WindowConfig
	{
		uint32_t width = 0, height = 0;
		bool maximize = false, vSync = true;
		std::string title = "";
	};

	class Window
	{
	public:
		void Init(const WindowConfig& windowConfig);
		void Shutdown();

		void PollEvents();
		void SwapBuffers();

		PINLINE uint32_t GetWidth() { return m_config.width; }
		PINLINE uint32_t GetHeight() { return m_config.height; }

		PINLINE bool IsMaximized() { return m_config.maximize; }
		PINLINE void* GetHandle() { return m_handle; }

		PINLINE bool IsVSync() { return m_config.vSync; }
		void SetVSync(bool enable);

	private:
		void* m_handle = nullptr;
		WindowConfig m_config;
		std::unique_ptr<Context> m_context;
	};
}
