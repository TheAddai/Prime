#pragma once

namespace prime {

	class Renderer2D
	{
	private:
		static void Init();
		static void Shutdown();

		static void InitSpriteRendering();
		static void ShutdownSpriteRendering();

	private:
		friend class Engine;
	};
}
