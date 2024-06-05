#pragma once

#include "engine/core/core.h"
#include "engine/renderer/uniform_buffer.h"

namespace prime {

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding);

		~OpenGLUniformBuffer() override;

		void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;
		PINLINE uint32_t GetBinding() { return m_binding; }

	private:
		uint32_t m_handle = 0, m_binding = 0;;
	};
}
