#pragma once

#include "engine/core/ref.h"

namespace prime {

	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}

		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;
		virtual uint32_t GetBinding() = 0;

		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};
}