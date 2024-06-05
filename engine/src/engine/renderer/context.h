#pragma once

#include "engine/core/window.h"

#include <memory>

namespace prime {

	class Context 
	{
	public:
		virtual void Init(Window& window) = 0;
		virtual void Shutdown() = 0;

		virtual void SwapBuffers() = 0;

		static std::unique_ptr<Context> Create();
	};
}