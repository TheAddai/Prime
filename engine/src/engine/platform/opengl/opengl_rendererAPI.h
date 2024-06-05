#pragma once

#include "engine/renderer/rendererAPI.h"

namespace prime {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init();
		void SetClearColor(const glm::vec4& color);
		void Clear();

		void Submit(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
	};
}