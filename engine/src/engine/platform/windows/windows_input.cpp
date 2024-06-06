
#include "pch.h"
#include "engine/core/input.h"
#include "engine/platform/platform.h"
#include "engine/engine.h"

#ifdef PPLATFORM_WINDOWS
#include <GLFW/glfw3.h>

namespace prime {

	bool Input::IsKeyPressed(const Key key)
	{
		GLFWwindow* window = (GLFWwindow*)Engine::GetWindow().GetHandle();
		auto state = glfwGetKey(window, static_cast<int>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const Button button)
	{
		GLFWwindow* window = (GLFWwindow*)Engine::GetWindow().GetHandle();
		auto state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = (GLFWwindow*)Engine::GetWindow().GetHandle();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}

#endif // PPLATFORM_WINDOWS