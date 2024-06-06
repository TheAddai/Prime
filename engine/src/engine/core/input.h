#pragma once

#include "keys.h"
#include "buttons.h"

#include <glm/glm.hpp>

namespace prime {

	class Input
	{
	public:
		static bool IsKeyPressed(const Key key);

		static bool IsMouseButtonPressed(const Button button);
		static glm::vec2 GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();
	};
}
