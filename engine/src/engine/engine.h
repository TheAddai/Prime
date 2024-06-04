#pragma once

#include "core/app.h"

int main(int argc, char** argv);

namespace prime {

	class Engine
	{
	public:
		static void Close();

	private:
		static void Run(App* app);

	private:
		friend int::main(int argc, char** argv);
	};
}
