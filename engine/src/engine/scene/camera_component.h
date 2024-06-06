#pragma once

#include "engine/renderer/camera.h"

namespace prime {

	class CameraComponent
	{
	public:
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

	public:
		Camera camera;
		glm::vec4 clearColor = { 0.1f, 0.1f, 0.8f, 1.0f };
		bool fixedAspectRatio = false;
	};
}