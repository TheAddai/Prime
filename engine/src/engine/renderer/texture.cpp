
#include "pch.h"
#include "texture.h"
#include "renderer.h"

// opengl
#include "engine/platform/opengl/opengl_texture.h"

namespace prime {

	Ref<Texture2D> Texture2D::Create(const TextureConfig& config)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return CreateRef<OpenGLTexture2D>(config);
			break;
		}
		return nullptr;
	}
}