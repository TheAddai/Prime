
#include "editor.h"

namespace prime {

	void Editor::Init()
	{
		RenderCommand::SetClearColor({ .2f, .2f, .2f, 1.0f });
	}

	void Editor::Shutdown()
	{

	}

	void Editor::Update(Timestep& timestep)
	{
		RenderCommand::Clear();
	}
}