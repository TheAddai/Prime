#pragma once

#include "engine/engine.h"

namespace prime {

	class Editor : public App
	{
	public:
		Editor() = default;

		void Init() override;
		void Shutdown() override;

		void Update() override;
	};
}
