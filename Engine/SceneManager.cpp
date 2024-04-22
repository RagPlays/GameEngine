#include <iostream>
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::GameStart()
{
	for (auto& scene : m_Scenes)
	{
		scene->GameStart();
	}
}

void SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void SceneManager::LateUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate();
	}
}

void SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const std::shared_ptr<Scene>& scene{ std::shared_ptr<Scene>(new Scene{ name }) };
	m_Scenes.push_back(scene);
	return *scene;
}

bool SceneManager::Empty() const
{
	return m_Scenes.empty();
}

void SceneManager::SetCurrentSceneByIndex(unsigned int idx)
{
	if (idx >= m_Scenes.size())
	{
		assert(false);
		std::cerr << "ERROR::SCENEMANAGER::SCENE_IDX_NOT_VALID\n";
	}

	m_CurrentSceneIdx = idx;
}

void SceneManager::SetCurrentSceneByName(const std::string& name)
{
	for (size_t idx{}; idx < m_Scenes.size(); ++idx)
	{
		if (m_Scenes[idx]->GetName() == name)
		{
			m_CurrentSceneIdx = static_cast<unsigned int>(idx);
			return;
		}
	}

	std::cerr << "ERROR::SCENEMANAGER::SCENE_NAME_NOT_VALID\n";
}

// Private Functions //

SceneManager::SceneManager()
	: m_CurrentSceneIdx{ 0 }
{
}