
#include "pch.h"
#include "vertex_array.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_vertex_array.h"

namespace prime {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLVertexArray>();
			break;
		}
		return nullptr;
	}
}