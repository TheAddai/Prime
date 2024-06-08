#pragma once

#include <string>
#include <glm/glm.hpp>

namespace prime {

	void DrawVec2Control(const std::string& label, glm::vec2& values, float resetValue = 0.0f, float columnWidth = 100.0f);
}
