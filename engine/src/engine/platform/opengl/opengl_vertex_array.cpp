
#include "pch.h"
#include "opengl_vertex_array.h"
#include "engine/core/assert.h"

#include <glad/glad.h>

namespace prime {

	static GLenum VertexTypeToOpenglType(VertexType vertexType)
	{
		switch (vertexType)
		{
		case VertexType::position: 
		case VertexType::color: 
		case VertexType::textureCoords: 
		case VertexType::textureIndex: 
			return GL_FLOAT; break;
		}
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_handle);
		glBindVertexArray(m_handle);
		m_index = 0;
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_handle);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_handle);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		PASSERT_MSG(vertexBuffer->GetLayout().GetVertices().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_handle);
		vertexBuffer->Bind();

		for (const Vertex& vertex : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(m_index);
			glVertexAttribPointer(m_index,
				vertex.GetCount(),
				VertexTypeToOpenglType(vertex.type),
				GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)(intptr_t)vertex.offset);

			m_index++;
		}

		m_vertexBuffer = vertexBuffer;
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_handle);
		indexBuffer->Bind();
		m_indexBuffer = indexBuffer;
	}
}