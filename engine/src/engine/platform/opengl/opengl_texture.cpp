
#include "pch.h"
#include "opengl_texture.h"
#include "engine/utils/helpers.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace prime {

	static uint32_t s_whiteData = 0xffffffff;

	OpenGLTexture2D::OpenGLTexture2D(const TextureConfig& config)
	{
		m_config = config;

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
		SetFilterAndWrap();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, config.width, config.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &s_whiteData);

		if (m_config.generateMips) { glGenerateMipmap(GL_TEXTURE_2D); }
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = nullptr;
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			m_path = path;
			m_config.width = width;
			m_config.height = height;

			glGenTextures(1, &m_handle);
			glBindTexture(GL_TEXTURE_2D, m_handle);
			SetFilterAndWrap();

			uint32_t dataFormat = TextureFormatToOpenGLDataFormat(m_config.format);
			uint32_t internalFormat = TextureFormatToOpenGLInternalFormat(m_config.format);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_config.width,
				m_config.height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

			if (m_config.generateMips) { glGenerateMipmap(GL_TEXTURE_2D); }
			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_handle);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	void OpenGLTexture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void OpenGLTexture2D::SetFilterAndWrap()
	{
		if (m_config.generateMips)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		glTexParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}