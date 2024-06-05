
#include "pch.h"
#include "engine/platform/platform.h"
#include "engine/utils/timer.h"

#ifdef PPLATFORM_WINDOWS
#include <GLFW/glfw3.h>
#endif // PPLATFORM_WINDOWS

namespace prime {

	float Timer::GetTime()
	{
		return (float)glfwGetTime();
	}
}