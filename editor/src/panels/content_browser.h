#pragma once

#include "engine/renderer/texture.h"

#include <filesystem>

namespace prime {

	class ContentBrowser
	{
	public:
		ContentBrowser() = default;

		void Init();
		void ImGuiRender();

	private:
		std::filesystem::path m_baseDirectory;
		std::filesystem::path m_currentDirectory;

		Ref<Texture2D> m_fileIcon;
		Ref<Texture2D> m_folderIcon;
	};
}