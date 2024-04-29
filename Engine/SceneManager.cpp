#include <iostream>
#include "SceneManager.h"
#include "Scene.h"
#include "EventQueue.h"

void SceneManager::GameStart()
{
	EventQueue::Get().AddEvent(GameEvent::gameStarts);
	m_Scenes[m_CurrentSceneIdx]->GameStart();
}

void SceneManager::FixedUpdate()
{
	m_Scenes[m_CurrentSceneIdx]->FixedUpdate();
}

void SceneManager::Update()
{
	m_Scenes[m_CurrentSceneIdx]->Update();
}

void SceneManager::LateUpdate()
{
	m_Scenes[m_CurrentSceneIdx]->LateUpdate();
}

void SceneManager::Render() const
{
	m_Scenes[m_CurrentSceneIdx]->Render();
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const std::shared_ptr<Scene>& scene{ std::shared_ptr<Scene>(new Scene{ name }) };
	m_Scenes.emplace_back(scene);
	return *scene;
}

void SceneManager::Destroy()
{
	for (auto& scene : m_Scenes)
	{
		scene.reset();
	}
	m_Scenes.clear();
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