#pragma once

#include "engine/renderer/shader.h"

namespace prime {

	class FileSystem
	{
	public:
		static Ref<Shader> Loadshader(const std::string& vertexShaderSource, const std::string& pixelShaderSource);

		static std::string LoadFile(std::string filepath);
	};
}
