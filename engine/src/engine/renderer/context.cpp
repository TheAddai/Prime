
#include "pch.h"
#include "context.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_context.h"

namespace prime {

	std::unique_ptr<Context> Context::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return std::make_unique<OpenGLContext>();
			break;
		}
		return nullptr;
	}
}