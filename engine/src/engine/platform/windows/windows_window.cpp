
#include "pch.h"
#include "engine/core/window.h"
#include "engine/platform/platform.h"
#include "engine/core/assert.h"
#include "engine/events/all.h"

#ifdef PPLATFORM_WINDOWS

#include <GLFW/glfw3.h>

namespace prime {

	static void GLFWErrorCallback(int error, const char* description)
	{
		PERROR("GLFW Error ({0}): {1}", error, description);
	}

	static void SetCallbacks(GLFWwindow* windowHandle)
	{
		glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowConfig& config = *(WindowConfig*)glfwGetWindowUserPointer(window);
				config.width = width;
				config.height = height;

				Dispatcher::Get().enqueue<WindowResizeEvent>(width, height);
			});

		glfwSetWindowCloseCallback(windowHandle, [](GLFWwindow* window)
			{
				Dispatcher::Get().enqueue<WindowCloseEvent>();

			});

		glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowConfig& config = *(WindowConfig*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					Dispatcher::Get().enqueue<KeyPressedEvent>((Key)key, false);
					break;
				}
				case GLFW_RELEASE:
				{
					Dispatcher::Get().enqueue<KeyReleasedEvent>((Key)key);
					break;
				}
				case GLFW_REPEAT:
				{
					Dispatcher::Get().enqueue<KeyPressedEvent>((Key)key, true);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowConfig& config = *(WindowConfig*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					Dispatcher::Get().enqueue<MouseButtonPressedEvent>((Button)button);
					break;
				}
				case GLFW_RELEASE:
				{
					Dispatcher::Get().enqueue<MouseButtonReleasedEvent>((Button)button);
					break;
				}
				}
			});

		glfwSetScrollCallback(windowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Dispatcher::Get().enqueue<MouseScrolledEvent>((float)xOffset, (float)yOffset);
			});

		glfwSetCursorPosCallback(windowHandle, [](GLFWwindow* window, double xPos, double yPos)
			{
				Dispatcher::Get().enqueue<MouseMovedEvent>((float)xPos, (float)yPos);
			});
	}

	void Window::Init(const WindowConfig& windowConfig)
	{
		uint8_t status = glfwInit();
		PASSERT_MSG(status, "Glfw failed to initialize");
		glfwSetErrorCallback(GLFWErrorCallback);

		m_config = windowConfig;
		if (m_config.maximize) { glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); }
		GLFWwindow* window = glfwCreateWindow(m_config.width, m_config.height, m_config.title.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer((GLFWwindow*)window, &m_config);
		SetCallbacks((GLFWwindow*)window);
		m_handle = window;

		m_context = Context::Create();
		m_context->Init(m_handle);
		SetVSync(m_config.vSync);
	}

	void Window::Shutdown()
	{
		m_context->Shutdown();
		glfwDestroyWindow((GLFWwindow*)m_handle);
		glfwSetErrorCallback(NULL);
		glfwTerminate();
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
	
	void Window::SwapBuffers()
	{
		m_context->SwapBuffers();
	}
	
	void Window::SetVSync(bool enable)
	{
		if (enable) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }
		m_config.vSync = enable;
	}
}

#endif // PPLATFORM_WINDOWS