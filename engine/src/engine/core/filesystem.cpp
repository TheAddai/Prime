
#include "pch.h"
#include "filesystem.h"
#include "engine/renderer/renderer.h"
#include "logger.h"

// opengl
#include "engine/platform/opengl/opengl_texture.h"

namespace prime {

	static std::string LoadFile(std::string filepath)
	{
		std::string result;
		std::ifstream file(filepath, std::ios::in | std::ios::binary);
		if (file)
		{
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			if (size != -1)
			{
				result.resize(size);
				file.seekg(0, std::ios::beg);
				file.read(&result[0], size);
			}
			else { PERROR("Could not read from file '{0}'", filepath); }
		}
		else { PERROR("Could not open file '{0}'", filepath); }
		return result;
	}

	static std::map<std::pair<std::string, std::string>, Ref<Shader>> s_shaders;
	static std::map<std::string, Ref<Texture2D>> s_textures;

	static bool ShaderExist(std::pair< std::string, std::string> shaderSources)
	{
		return s_shaders.find(shaderSources) != s_shaders.end();
	}

	static bool TextureExist(std::string path)
	{
		return s_textures.find(path) != s_textures.end();
	}

	Ref<Shader> Filesystem::Loadshader(const std::string& vertexShaderSource, const std::string& pixelShaderSource)
	{
		std::pair<std::string, std::string> shaderSources;
		shaderSources.first = vertexShaderSource;
		shaderSources.second = pixelShaderSource;

		if (ShaderExist(shaderSources)) { return s_shaders[shaderSources]; }
		else
		{
			std::string vertexSource = LoadFile(shaderSources.first);
			std::string pixelSource = LoadFile(shaderSources.second);
			Ref<Shader> shader = Shader::Create(vertexSource, pixelSource);

			s_shaders[shaderSources] = shader;
			return shader;
		}
	}

	Ref<Texture2D> Filesystem::LoadTexture(const std::string& path)
	{
		if (TextureExist(path)) { return s_textures[path]; }
		else
		{
			Ref<Texture2D> texture;
			switch (Renderer::GetGraphicsAPI())
			{
			case graphicsAPIOpenGL:
				texture = CreateRef<OpenGLTexture2D>(path);
				break;
			}

			s_textures[path] = texture;
			return texture;
		}
	}
}
