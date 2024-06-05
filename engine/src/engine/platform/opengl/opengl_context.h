#pragma once

#include "engine/renderer/context.h"

namespace prime {

	class OpenGLContext : public Context
	{
	public:
		OpenGLContext() = default;

		void Init(void* windowHandle);
		void Shutdown();

		void SwapBuffers();

	private:
		void* m_windowHandle = nullptr;
	};
}
