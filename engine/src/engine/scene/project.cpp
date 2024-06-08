
#include "pch.h"
#include "project.h"

namespace prime {

	Project::Project(const ProjectConfig& config)
	{
		Ref<Scene> m_scene;
		m_scene = Scene::Create(this, "SampleScene");
		m_scenes[m_activeSceneIndex] = m_scene;
	}

	Ref<Project> Project::Create(const ProjectConfig& config)
	{
		return CreateRef<Project>(config);
	}
}