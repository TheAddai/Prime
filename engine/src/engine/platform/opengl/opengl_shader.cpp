
#include "pch.h"
#include "opengl_shader.h"
#include "engine/core/assert.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace prime {

	OpenGLShader::OpenGLShader(const std::string& vertexShader, const std::string& PixelShader)
	{
		m_vertexShader = Compile(vertexShader.c_str(), GL_VERTEX_SHADER);
		m_pixelShader = Compile(PixelShader.c_str(), GL_FRAGMENT_SHADER);
		m_program = Generate(m_vertexShader, m_pixelShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDetachShader(m_program, m_vertexShader);
		glDetachShader(m_program, m_pixelShader);
		glDeleteProgram(m_program);
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_pixelShader);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_program);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat2(const std::string& name, const glm::mat2& value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	uint32_t OpenGLShader::Compile(const char* shaderSource, int shaderType)
	{
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderSource, 0);
		glCompileShader(shader);

		// check to see if it compile
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == 0)
		{
			GLint max_length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
			char log_message[2000];
			memset(log_message, 0, sizeof(log_message));
			glGetShaderInfoLog(shader, max_length, &max_length, log_message);

			if (shaderType == GL_VERTEX_SHADER) { PERROR("vertex shader compilation failed"); }
			if (shaderType == GL_FRAGMENT_SHADER) { PERROR("fragment shader compilation failed"); }
			PERROR("{0}", log_message);
			PASSERT(false);
		}
		return shader;
	}

	uint32_t OpenGLShader::Generate(uint32_t vertexShader, uint32_t pixelShader)
	{
		uint32_t program = glCreateProgram();

		glAttachShader(program, vertexShader);
		glAttachShader(program, pixelShader);
		glLinkProgram(program);

		// check if mProgram linked
		GLint linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (linked == 0)
		{
			GLint max_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
			char log_message[4000];
			memset(log_message, 0, sizeof(log_message));
			glGetProgramInfoLog(program, max_length, &max_length, log_message);

			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(pixelShader);

			PERROR("{0}", log_message);
			PASSERT_MSG(false, "program linking failed");
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, pixelShader);
		return program;
	}
}