
#include "pch.h"
#include "opengl_uniform_buffer.h"

#include <glad/glad.h>

namespace prime {

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
	{
		glGenBuffers(1, &m_handle);
		glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_handle);
		m_binding = binding;
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_handle);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	}
}