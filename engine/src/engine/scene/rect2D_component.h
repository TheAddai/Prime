#pragma once

#include <glm/glm.hpp>

namespace prime {

	class Rect2DComponent
	{
	public:
		Rect2DComponent() = default;
		Rect2DComponent(const Rect2DComponent&) = default;
		Rect2DComponent(const glm::vec4& color) : color(color) {}

	public:
		glm::vec4 color = glm::vec4(1.0f);
	};
}
