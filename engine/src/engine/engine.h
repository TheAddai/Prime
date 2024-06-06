#pragma once

#include "core/app.h"
#include "core/window.h"

int main(int argc, char** argv);

namespace prime {

	class Engine
	{
	public:
		static void Close();

		static Window& GetWindow();

	private:
		static void Run(App* app);

	private:
		friend int::main(int argc, char** argv);
	};
}
