#pragma once

#include <glm/glm.hpp>

namespace prime {

	class TransformComponent;
	class SpriteComponent;

	class Renderer2D
	{
	public:
		static void Begin(const glm::mat4 viewProjectionMatrix);
		static void End();

		static void DrawSprite(TransformComponent transform, SpriteComponent sprite);

	private:
		static void Init();
		static void Shutdown();

		static void InitSpriteRendering();
		static void ShutdownSpriteRendering();

	private:
		friend class Engine;
	};
}
