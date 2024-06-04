#pragma once

#include "core/platform.h"
#include "engine.h"

#ifdef PPLATFORM_WINDOWS
int main(int argc, char** argv)
{
	prime::App* app = prime::CreateApplication();
	prime::Engine::Run(app);

	delete app;
	app = nullptr;
}
#endif // PPLATFORM_WINDOWS
