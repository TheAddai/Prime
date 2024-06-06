#pragma once

#include <glm/glm.hpp>

namespace prime {

	class RectComponent
	{
	public:
		RectComponent() = default;
		RectComponent(const RectComponent&) = default;
		RectComponent(const glm::vec4& color) : color(color) {}

	public:
		glm::vec4 color = glm::vec4(1.0f);
	};
}
