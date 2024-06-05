
#include "pch.h"
#include "rendererAPI.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_rendererAPI.h"

namespace prime {

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return std::make_unique<OpenGLRendererAPI>();
			break;
		}
		return nullptr;
	}
}