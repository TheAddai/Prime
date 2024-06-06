#pragma once

#include "engine/renderer/shader.h"
#include "engine/renderer/texture.h"

namespace prime {

	class Filesystem
	{
	public:
		static Ref<Shader> Loadshader(const std::string& vertexShaderSource, const std::string& pixelShaderSource);
		static Ref<Texture2D> LoadTexture(const std::string& path);
	};
}
