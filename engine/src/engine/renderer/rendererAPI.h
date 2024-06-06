#pragma once

#include "vertex_array.h"

#include <memory>
#include <glm/glm.hpp>

namespace prime {

	class RendererAPI
	{
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void Submit(const Ref<VertexArray>& vertexArray, uint32_t indexCount) = 0;
		virtual void SetViewport(uint32_t width, uint32_t height) = 0;

		static std::unique_ptr<RendererAPI> Create();
	};
}