
#include "pch.h"
#include "shader.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_shader.h"

namespace prime {

	Ref<Shader> Shader::Create(const std::string& vertexShaderSource, const std::string& PixelShaderSource)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLShader>(vertexShaderSource, PixelShaderSource);
			break;
		}
		return nullptr;
	}
}