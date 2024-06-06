#pragma once

#include <glm/glm.hpp>

namespace prime {

	class LineComponent
	{
	public:
		LineComponent() = default;
		LineComponent(const LineComponent&) = default;

	public:
		glm::vec3  endPosition = glm::vec3(1.0f);
		glm::vec4 color = glm::vec4(1.0f);
	};
}