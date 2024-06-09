
#include "pch.h"
#include "project.h"

namespace prime {

	Project::Project(const ProjectConfig& config)
	{
		Ref<Scene> m_scene;
		m_scene = Scene::Create(this, "SampleScene");
		m_scenes.push_back(m_scene);

		m_config = config;
		std::filesystem::create_directory(config.path / config.name);
		// Assets
		std::filesystem::create_directory(config.path / config.name / "Assets");
		// Scenes
		std::filesystem::create_directory(config.path / config.name / "Scenes");
	}

	Ref<Project> Project::Create(const ProjectConfig& config)
	{
		return CreateRef<Project>(config);
	}
}