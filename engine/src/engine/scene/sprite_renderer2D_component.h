#pragma once

#include "engine/renderer/texture.h"

#include <glm/glm.hpp>

namespace prime {

	class SpriteRenderer2DComponent
	{
	public:
		SpriteRenderer2DComponent() = default;
		SpriteRenderer2DComponent(const SpriteRenderer2DComponent&) = default;
		SpriteRenderer2DComponent(const glm::vec4& color) : color(color) {}

	public:
		glm::vec4 color = glm::vec4(1.0f);
		Ref<Texture2D> texture;
	};
}