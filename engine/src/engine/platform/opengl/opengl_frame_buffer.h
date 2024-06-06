#pragma once

#include "engine/renderer/frame_buffer.h"
#include "engine/core/assert.h"

namespace prime {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferConfig& config);
		~OpenGLFramebuffer() override;

		void Resize(uint32_t width, uint32_t height) override;

		void Bind() override;
		void Unbind() override;

		uint32_t GetHandleID() const override { return m_handle; }

		uint32_t GetTextureID(uint32_t index) override
		{ PASSERT(index < m_textures.size()); return m_textures[index]; }

		uint32_t GetWidth() const override { return m_config.width; }
		uint32_t GetHeight() const override { return m_config.height; }

	private:
		void Generate();

	private:
		uint32_t m_handle = 0;
		FramebufferConfig m_config;

		std::vector<FramebufferTextureConfig> m_textureConfig;
		FramebufferTextureConfig m_depthConfig = FramebufferTextureFormat::none;

		std::vector<uint32_t> m_textures;
		uint32_t m_depth = 0;
	};
}