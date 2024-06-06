
#include "pch.h"
#include "imguiAPI.h"
#include "engine/renderer/renderer.h"

// openGL
#include "gl_imguiAPI.h"

namespace prime {

	std::unique_ptr<ImGuiAPI> ImGuiAPI::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case graphicsAPIOpenGL:
			return std::make_unique<GLImGuiAPI>();
			break;
		}
		return nullptr;
	}
}
