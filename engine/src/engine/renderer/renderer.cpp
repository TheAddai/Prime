
#include "pch.h"
#include "renderer.h"

namespace prime {

	static GraphicsAPI s_graphicsAPI;

	GraphicsAPI Renderer::GetGraphicsAPI()
	{
		return s_graphicsAPI;
	}

	void Renderer::SetGraphicsAPI(GraphicsAPI graphicsAPI)
	{
		s_graphicsAPI = graphicsAPI;
	}
}