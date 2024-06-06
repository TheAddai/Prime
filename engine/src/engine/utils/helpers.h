#pragma once

namespace prime {

	enum class TextureFormat;

	uint32_t TextureFormatToOpenGLDataFormat(TextureFormat format);

	uint32_t TextureFormatToOpenGLInternalFormat(TextureFormat format);
}