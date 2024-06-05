#pragma once

#include "engine/renderer/vertex_buffer.h"

namespace prime {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;

		const VertexLayout& GetLayout() const override { return m_layout; }
		void SetLayout(const VertexLayout& layout) override { m_layout = layout; }

	private:
		uint32_t m_handle = 0;
		VertexLayout m_layout;
	};
}