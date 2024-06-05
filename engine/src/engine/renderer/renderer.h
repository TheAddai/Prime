#pragma once

namespace prime {

	enum GraphicsAPI
	{
		graphicsAPIOpenGL
	};

	class Renderer
	{
	public:
		static GraphicsAPI GetGraphicsAPI();

	private:
		static void SetGraphicsAPI(GraphicsAPI graphicsAPI);

		friend class Engine;
	};
}