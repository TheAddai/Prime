#pragma once

#include "engine/renderer/shader.h"

namespace prime {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexShader, const std::string& PixelShader);

		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;

		void SetMat2(const std::string& name, const glm::mat2& value) override;
		void SetMat3(const std::string& name, const glm::mat3& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;

	private:
		uint32_t Compile(const char* shaderSource, int shaderType);
		uint32_t Generate(uint32_t vertexShader, uint32_t pixelShader);

	private:
		uint32_t m_vertexShader = 0, m_pixelShader = 0;
		uint32_t m_program = 0;
	};
}
