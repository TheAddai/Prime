#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace prime {

	class RendererAPI
	{
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		static std::unique_ptr<RendererAPI> Create();
	};
}