#pragma once

#include <glm/glm.hpp>

namespace prime {

	class TransformComponent
	{
	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& position) : position(position) {}

	public:
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
		glm::vec3 rotation = glm::vec3(0.0f);
	};
}