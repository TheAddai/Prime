#pragma once

#include "engine/core/core.h"

#include <entt/entt.hpp>

namespace prime {

	class Dispatcher
	{
	public:
		static entt::dispatcher& Get() { return m_dispatcher; }

	private:
		PINLINE static entt::dispatcher m_dispatcher;
	};
}