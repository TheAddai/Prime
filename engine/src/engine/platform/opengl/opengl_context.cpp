
#include "pch.h"
#include "opengl_context.h"
#include "engine/core/assert.h"

#ifdef PPLATFORM_WINDOWS
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif // PPLATFORM_WINDOWS

namespace prime {

	void OpenGLContext::Init(void* windowHandle)
	{
		PASSERT_MSG(windowHandle, "Window is null");
		m_windowHandle = windowHandle;

#ifdef PPLATFORM_WINDOWS
		glfwMakeContextCurrent((GLFWwindow*)m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PASSERT_MSG(status, "Failed to initialize Glad!");
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