#pragma once

namespace prime {

	class App
	{
	public:
		virtual void Init() {}
		virtual void Shutdown() {}

		virtual void Update() {}
	};

	App* CreateApplication();
}
