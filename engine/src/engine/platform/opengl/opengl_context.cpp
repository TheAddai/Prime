
#include "pch.h"
#include "opengl_context.h"
#include "engine/core/assert.h"

#ifdef PPLATFORM_WINDOWS
#include <GLFW/glfw3.h>
#endif // PPLATFORM_WINDOWS

namespace prime {

	void OpenGLContext::Init(Window& window)
	{
		PASSERT_MSG(window.GetHandle(), "Window is null");
		m_windowHandle = window.GetHandle();

#ifdef PPLATFORM_WINDOWS
		glfwMakeContextCurrent((GLFWwindow*)m_windowHandle);
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::Shutdown()
	{
		// the opengl context is deleted internally by glfw
	}

	void OpenGLContext::SwapBuffers()
	{
#ifdef PPLATFORM_WINDOWS
		glfwSwapBuffers((GLFWwindow*)m_windowHandle);
#endif // PPLATFORM_WINDOWS
	}
}