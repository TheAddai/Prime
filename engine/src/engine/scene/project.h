#pragma once

#include "scene.h"
#include "engine/core/app.h"

#include <vector>
#include <filesystem>

namespace prime {

	struct ProjectConfig
	{
		AppType type = AppType::appType2D;
		std::string name = "Prime Project";
		std::filesystem::path path = "";
	};

	class Project
	{
	public:
		Project() = default;
		Project(const ProjectConfig& config);

		std::filesystem::path GetPath() { return m_config.path; }
		std::filesystem::path GetAssetsPath() {  return GetPath() / "Assets"; }
		std::filesystem::path GetScenesPath() {  return GetPath() / "Scenes"; }

		Ref<Scene>& GetActiveScene() { return m_scenes.at(m_activeSceneIndex); }

		static Ref<Project> Create(const ProjectConfig& config);

	private:
		ProjectConfig m_config;
		std::vector<Ref<Scene>> m_scenes;
		uint32_t m_activeSceneIndex = 0;

		friend class Scene;

	};
}
