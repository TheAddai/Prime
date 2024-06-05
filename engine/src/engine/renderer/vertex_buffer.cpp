
#include "pch.h"
#include "vertex_buffer.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_vertex_buffer.h"

namespace prime {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
			break;
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
			break;
		}
		return nullptr;
	}
}