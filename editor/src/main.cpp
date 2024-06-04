
#include "engine/entry.h"
#include "editor.h"

prime::App* prime::CreateApplication()
{
	return new Editor();
}