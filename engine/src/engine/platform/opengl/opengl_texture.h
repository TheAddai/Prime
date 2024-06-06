#pragma once

#include "engine/renderer/texture.h"

namespace prime {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureConfig& config);
		OpenGLTexture2D(const std::string& path);

		~OpenGLTexture2D() override;

		uint32_t GetWidth() const override { return m_config.width; }
		uint32_t GetHeight() const override { return m_config.height; }

		uint32_t GetHandle() const override { return m_handle; }
		TextureFormat GetFormat() const override { return m_config.format; }

		const std::string& GetPath() const override { return m_path; }

		void Bind(uint32_t slot = 0) const override;
		void Unbind() const override;

		bool operator==(const Texture& other) const override
		{
			return m_handle == other.GetHandle();
		}

	private:
		void SetFilterAndWrap();

	private:
		uint32_t m_handle = 0;
		TextureConfig m_config;
		std::string m_path = "";
	};
}