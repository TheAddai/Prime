
#include "pch.h"
#include "math.h"
#include "engine/scene/transform_component.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace prime {

	glm::mat4 GetTransform(TransformComponent transform)
	{
		glm::mat4 rot = glm::toMat4(glm::quat(transform.rotation));

		return glm::translate(glm::mat4(1.0f), transform.position)
			* rot
			* glm::scale(glm::mat4(1.0f), transform.scale);
	}

	glm::mat4 GetTransformNoScale(TransformComponent transform)
	{
		glm::mat4 rot = glm::toMat4(glm::quat(transform.rotation));

		return glm::translate(glm::mat4(1.0f), transform.position)
			* rot;
	}
}