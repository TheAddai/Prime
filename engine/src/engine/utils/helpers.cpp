
#include "pch.h"
#include "helpers.h"
#include "engine/core/assert.h"
#include "engine/renderer/texture.h"

#include <glad/glad.h>

namespace prime {

	uint32_t TextureFormatToOpenGLDataFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB8:  return GL_RGB;
		case TextureFormat::RGBA8: return GL_RGBA;
		}

		PASSERT(false);
		return 0;
	}

	uint32_t TextureFormatToOpenGLInternalFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB8:  return GL_RGB8;
		case TextureFormat::RGBA8: return GL_RGBA8;
		}

		PASSERT(false);
		return 0;
	}
}