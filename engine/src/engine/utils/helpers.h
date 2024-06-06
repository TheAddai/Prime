#pragma once

namespace prime {

	enum class TextureFormat;
	enum class FramebufferTextureFormat;

	uint32_t TextureFormatToOpenGLDataFormat(TextureFormat format);

	uint32_t TextureFormatToOpenGLInternalFormat(TextureFormat format);

	uint32_t TextureTarget(bool multisampled);

	bool IsDepthFormat(FramebufferTextureFormat format);

	void AttachTexture(uint32_t id, uint32_t samples, uint32_t intFormat, uint32_t format, uint32_t width, uint32_t height, uint32_t index);

	void AttachDepth(uint32_t id, uint32_t samples, uint32_t format, uint32_t type, uint32_t width, uint32_t height);
}