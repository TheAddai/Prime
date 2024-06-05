
#include "pch.h"
#include "index_buffer.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_index_buffer.h"

namespace prime {

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
			break;
		}
		return nullptr;
	}
}