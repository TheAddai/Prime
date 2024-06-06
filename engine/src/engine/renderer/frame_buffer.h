#pragma once

#include "engine/core/ref.h"

#include <vector>

namespace prime {

	enum class FramebufferTextureFormat
	{
		none = 0,

		// color
		RGBA8,
		RED_INTEGER,

		// depth/stencil
		DEPTH24STENCIL8,

		// defaults
		depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureConfig
	{
		FramebufferTextureConfig() = default;
		FramebufferTextureConfig(FramebufferTextureFormat format)
			: textureFormat(format) {}

		FramebufferTextureFormat textureFormat = FramebufferTextureFormat::none;
	};

	struct FramebufferAttachmentConfig
	{
		FramebufferAttachmentConfig() = default;
		FramebufferAttachmentConfig(std::initializer_list<FramebufferTextureConfig> attachments)
			: attachments(attachments) {}

		std::vector<FramebufferTextureConfig> attachments;
	};

	struct FramebufferConfig
	{
		uint32_t width = 0, height = 0;
		FramebufferAttachmentConfig attachments;
		uint32_t samples = 1;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetHandleID() const = 0;
		virtual uint32_t GetTextureID(uint32_t index = 0) = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		static Ref<Framebuffer> Create(const FramebufferConfig& config);
	};
}