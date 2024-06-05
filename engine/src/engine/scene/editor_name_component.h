#pragma once

#include <string>

namespace prime {

	class EditorNameComponent
	{
	public:
		EditorNameComponent() = default;
		EditorNameComponent(const EditorNameComponent&) = default;
		EditorNameComponent(const std::string& name) : name(name) {}

	public:
		std::string name;
	};
}