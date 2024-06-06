
#include "pch.h"
#include "frame_buffer.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_frame_buffer.h"

namespace prime {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferConfig& config)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLFramebuffer>(config);
			break;
		}
		return nullptr;
	}
}