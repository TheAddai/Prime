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
		void DrawAddComponentButton();

		void DrawComponents(Entity entity);

	private:
		Entity m_selection;
	};
}
