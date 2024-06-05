#pragma once

#include "engine/core/core.h"
#include "rendererAPI.h"

namespace prime {

	class RenderCommand
	{
	public:
		static void SetClearColor(const glm::vec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_rendererAPI->Clear();
		}
		
		static void Submit(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			vertexArray->Bind();
			s_rendererAPI->Submit(vertexArray, indexCount);
		}

	private:
		static void Init()
		{
			if (!s_rendererAPI.get()) { s_rendererAPI = RendererAPI::Create(); }
			s_rendererAPI->Init();
		}

	private:
		PINLINE static std::unique_ptr<RendererAPI> s_rendererAPI;
		friend class Engine;
	};
}