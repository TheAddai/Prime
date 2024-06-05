
#include "pch.h"
#include "renderer.h"
#include "engine/core/logger.h"

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

	void Renderer::Init()
	{
		PERROR("Does not support 3D yet");
	}

	void Renderer::Shutdown()
	{
		PERROR("Does not support 3D yet");
	}
}