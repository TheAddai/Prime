#pragma once

#include "engine/all.h"

namespace prime {

	class Editor : public App
	{
	public:
		Editor() = default;

		void Init() override;
		void Shutdown() override;

		void Update(Timestep& timestep) override;
	};
}
