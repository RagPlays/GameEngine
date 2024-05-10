#include <iostream>
#include <cassert>

#include "SceneManager.h"
#include "Scene.h"
#include "EventQueue.h"
#include "GameEvents.h"

SceneManager::~SceneManager() = default;

void SceneManager::GameStart()
{
	if (!m_Scenes[m_CurrentSceneIdx]->IsLoaded())
	{
		m_Scenes[m_CurrentSceneIdx]->Load();
	}

	EventQueue::Get().AddEvent(GameEvent::gameStarts);
	m_Scenes[m_CurrentSceneIdx]->GameStart();
}

void SceneManager::FixedUpdate()
{
	m_Scenes[m_CurrentSceneIdx]->FixedUpdate();
}

void SceneManager::Update()
{
	CheckSceneSwap();
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

Scene& SceneManager::CreateScene(const std::string& name, std::function<void(Scene&)> loadFunc)
{
	std::unique_ptr<Scene> scene{ std::make_unique<Scene>(name, std::move(loadFunc)) };
	Scene* scenePtr{ scene.get() };
	m_Scenes.emplace_back(std::move(scene));
	return *scenePtr;
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

void SceneManager::SetCurrentSceneByIndex(uint8_t idx)
{
	if (idx >= m_Scenes.size())
	{
		assert(false);
		std::cerr << "ERROR::SCENEMANAGER::SCENE_IDX_NOT_VALID\n";
	}
	m_ToSceneIdx = idx;
}

void SceneManager::SetCurrentSceneByName(const std::string& name)
{
	for (size_t idx{}; idx < m_Scenes.size(); ++idx)
	{
		if (m_Scenes[idx]->GetName() == name)
		{
			SetCurrentSceneByIndex(static_cast<uint8_t>(idx));
			return;
		}
	}

	std::cerr << "ERROR::SCENEMANAGER::SCENE_NAME_NOT_VALID\n";
}

void SceneManager::GoNextScene()
{
	if ((m_CurrentSceneIdx + 1) >= m_Scenes.size())
	{
		assert(false);
		std::cerr << "ERROR::SCENEMANAGER::SCENE_IDX_NOT_VALID\n";
	}
	m_ToSceneIdx = m_CurrentSceneIdx + 1;
}

Scene& SceneManager::GetCurrentScene() const
{
	return *m_Scenes[m_CurrentSceneIdx];
}

uint8_t SceneManager::GetCurrentSceneIndex() const
{
	return m_CurrentSceneIdx;
}

// Private Functions //

SceneManager::SceneManager()
	: m_CurrentSceneIdx{ 0 }
	, m_ToSceneIdx{ 0 }
{
	m_Scenes.clear();
}

void SceneManager::CheckSceneSwap()
{
	if (m_ToSceneIdx != m_CurrentSceneIdx)
	{
		if (m_Scenes[m_CurrentSceneIdx]->IsLoaded())
		{
			m_Scenes[m_CurrentSceneIdx]->UnLoad();
		}
		m_CurrentSceneIdx = m_ToSceneIdx;
		m_Scenes[m_ToSceneIdx]->Load();
	}
}