#pragma once

#include "engine/core/GUID.h"

namespace prime {

	class IDComponent
	{
	public:
		IDComponent() = default;
		IDComponent(GUID _gUID) : gUID(_gUID) {};
		IDComponent(const IDComponent&) = default;

	public:
		GUID gUID;
	};
}