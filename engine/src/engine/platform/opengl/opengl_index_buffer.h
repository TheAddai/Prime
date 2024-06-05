#pragma once

#include "engine/core/core.h"
#include "engine/renderer/index_buffer.h"

namespace prime {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		PINLINE uint32_t GetCount() const { return m_count; }

	private:
		uint32_t m_handle = 0, m_count = 0;
	};
}
