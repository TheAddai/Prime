#pragma once

#include "engine/renderer/vertex_array.h"

namespace prime {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const Ref<VertexBuffer>& GetVertexBuffer() const override { return m_vertexBuffer; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_indexBuffer; }

	private:
		uint32_t m_handle = 0, m_index = 0;
		Ref<VertexBuffer> m_vertexBuffer;
		Ref<IndexBuffer> m_indexBuffer;
	};
}