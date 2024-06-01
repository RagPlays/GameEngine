#include <iostream>
#include <cassert>

#include "SceneManager.h"
#include "Scene.h"
#include "EventQueue.h"

namespace MoE
{
	SceneManager::~SceneManager() = default;

	void SceneManager::GameStart()
	{
		CheckSceneSwap();
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
		if (static_cast<size_t>(idx) >= m_Scenes.size())
		{
			assert(false);
			std::cerr << "ERROR::SCENEMANAGER::SCENE_IDX_NOT_VALID\n";
		}
		m_ToSceneIdx = idx;
		m_NeedSceneChange = true;
	}

	void SceneManager::SetCurrentSceneByName(const std::string& name)
	{
		for (size_t idx{}; idx < m_Scenes.size(); ++idx)
		{
			if (m_Scenes[idx]->GetName() == name)
			{
				return SetCurrentSceneByIndex(static_cast<uint8_t>(idx));
			}
		}
		std::cerr << "ERROR::SCENEMANAGER::SCENE_NAME_NOT_VALID\n";
	}

	void SceneManager::ReloadScene()
	{
		m_NeedSceneChange = true;
	}

	void SceneManager::GoNextScene()
	{
		SetCurrentSceneByIndex(m_CurrentSceneIdx + 1);
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
		: m_NeedSceneChange{ true }
		, m_ToSceneIdx{}
		, m_CurrentSceneIdx{ 255 }
		, m_Scenes{}
	{
		m_Scenes.clear();
	}

	void SceneManager::CheckSceneSwap()
	{
		if (!m_NeedSceneChange) return;

		if (m_CurrentSceneIdx < static_cast<uint8_t>(m_Scenes.size()))
		{
			if (m_Scenes[m_CurrentSceneIdx]->IsLoaded())
			{
				m_Scenes[m_CurrentSceneIdx]->SceneEnd();
				m_Scenes[m_CurrentSceneIdx]->UnLoad();
			}
		}
		if (m_ToSceneIdx < static_cast<uint8_t>(m_Scenes.size()))
		{
			m_CurrentSceneIdx = m_ToSceneIdx;
			m_Scenes[m_ToSceneIdx]->Load();
			m_Scenes[m_ToSceneIdx]->SceneStart();
		}
		else m_ToSceneIdx = m_CurrentSceneIdx;
		m_NeedSceneChange = false;
	}
}