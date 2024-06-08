#pragma once

#include <glm/glm.hpp>

namespace prime {

	class Line2DComponent
	{
	public:
		Line2DComponent() = default;
		Line2DComponent(const Line2DComponent&) = default;

	public:
		glm::vec2  endPosition = glm::vec2(1.0f);
		glm::vec4 color = glm::vec4(1.0f);
	};
}