
#include "pch.h"
#include "opengl_frame_buffer.h"
#include "engine/utils/helpers.h"

#include <glad/glad.h>

namespace prime {

	static const uint32_t s_maxFramebufferSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferConfig& config)
		: m_config(config)
	{
		for (FramebufferTextureConfig spec : m_config.attachments.attachments)
		{
			if (!IsDepthFormat(spec.textureFormat))
			{
				m_textureConfig.emplace_back(spec);
			}
			else
			{
				m_depthConfig = spec;
			}
		}
		Generate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_handle);
		glDeleteTextures((uint32_t)m_textures.size(), m_textures.data());
		glDeleteTextures(1, &m_depth);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_maxFramebufferSize || height > s_maxFramebufferSize)
		{
			PWARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_config.width = width;
		m_config.height = height;
		Generate();
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
		glViewport(0, 0, m_config.width, m_config.height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Generate()
	{
		if (m_handle)
		{
			glDeleteFramebuffers(1, &m_handle);
			glDeleteTextures((uint32_t)m_textures.size(), m_textures.data());
			glDeleteTextures(1, &m_depth);

			m_textures.clear();
			m_depth = 0;
		}

		glGenFramebuffers(1, &m_handle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
		bool multisample = m_config.samples > 1;

		// textures
		if (m_textures.size())
		{
			m_textures.resize(m_textureConfig.size());
			glGenTextures((uint32_t)m_textures.size(), m_textures.data());

			for (size_t i = 0; i < m_textures.size(); i++)
			{
				if (multisample) { glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_textures[i]); }
				else { glBindTexture(GL_TEXTURE_2D, m_textures[i]); }

				uint32_t index = (uint32_t)i;

				switch (m_textureConfig[i].textureFormat)
				{
				case FramebufferTextureFormat::RGBA8: 
					AttachTexture(m_textures[index], m_config.samples, GL_RGBA8, GL_RGBA, m_config.width, m_config.height, index);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					AttachTexture(m_textures[index], m_config.samples, GL_R32I, GL_RED_INTEGER, m_config.width, m_config.height, index);
					break;
				}
			}
		}

		// depth
		if (m_depthConfig.textureFormat != FramebufferTextureFormat::none)
		{
			glGenTextures(1, &m_depth);
			if (multisample) { glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_depth); }
			else { glBindTexture(GL_TEXTURE_2D, m_depth); }

			switch (m_depthConfig.textureFormat)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				AttachDepth(m_depth, m_config.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_config.width, m_config.height);
				break;
			}
		}

		if (m_textures.size() > 1)
		{
			PASSERT(m_textures.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((uint32_t)m_textures.size(), buffers);
		}
		else if (m_textures.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		PASSERT_MSG(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
