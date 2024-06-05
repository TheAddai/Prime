#pragma once

#include "engine/renderer/context.h"

namespace prime {

	class OpenGLContext : public Context
	{
	public:
		OpenGLContext() = default;

		void Init(Window& window);
		void Shutdown();

		void SwapBuffers();

	private:
		WindowHandle m_windowHandle = nullptr;
	};
}
