#pragma once

#include "engine/scene/components.h"

#include "texture.h"
#include <glm/glm.hpp>

namespace prime {

	class Renderer2D
	{
	public:
		static void Begin(const glm::mat4 viewProjectionMatrix);
		static void End();

		static void DrawSprite(TransformComponent transform, SpriteRenderer2DComponent sprite);
		static void DrawLine(TransformComponent transform, Line2DComponent line);
		static void DrawRect(TransformComponent transform, Rect2DComponent rect);

	private:
		static void Init();
		static void Shutdown();

		static void InitSpriteRendering();
		static void ShutdownSpriteRendering();

		static void InitLineRendering();
		static void ShutdownLineRendering();

		static void BeginRendering();
		static float GetTextureIndex(Ref<Texture2D>& texture);

	private:
		friend class Engine;
	};
}
