#pragma once

#include "engine/scene/entity.h"
#include "engine/scene/components.h"

namespace prime {

	class Properties
	{
	public:
		void ImGuiRender(Entity entity);

	private:
		void DrawNameComponent();

	private:
		Entity m_selection;
	};
}
