
#include "pch.h"
#include "uniform_buffer.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_uniform_buffer.h"

namespace prime {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLUniformBuffer>(size, binding);
			break;
		}
		return nullptr;
	}
}