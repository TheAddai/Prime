#pragma once

#include "engine/core/ref.h"

#include <string>

namespace prime {

	enum class TextureFormat
	{
		none = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	struct TextureConfig
	{
		uint32_t width = 1;
		uint32_t height = 1;
		TextureFormat format = TextureFormat::RGBA8;
		bool generateMips = true;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual uint32_t GetHandle() const = 0;
		virtual TextureFormat GetFormat() const = 0;

		virtual const std::string& GetPath() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind() const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const TextureConfig& config);
	};
}