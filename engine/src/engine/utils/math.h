#pragma once

#include <glm/glm.hpp>

namespace prime {

	class TransformComponent;

	glm::mat4 GetTransform(TransformComponent transform);
}
