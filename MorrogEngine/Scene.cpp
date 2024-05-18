#include "Scene.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "InputManager.h"
#include "EventQueue.h"

namespace MoE
{
	Scene::Scene(const std::string& name, std::function<void(Scene&)> loadFunc)
		: m_Name(name)
		, m_LoadFunction{ std::move(loadFunc) }
		, m_IsLoaded{ false }
	{
	}

	Scene::~Scene() = default;

	void Scene::Add(std::unique_ptr<GameObject>&& object)
	{
		m_Objects.emplace_back(std::move(object));
	}

	void Scene::Load()
	{
		m_LoadFunction(*this);
		m_IsLoaded = true;
	}

	void Scene::UnLoad()
	{
		// Unload GameObjects
		m_Objects.clear();
		// Unload Events
		EventQueue::Get().ClearEvents();
		// Unload EventHandlers
		EventQueue::Get().ClearHandlers();
		// Unload Sounds 
		ServiceLocator::GetSoundSystem().ClearSounds();
		// Unload Inputs 
		InputManager::Get().ClearBinds();

		m_IsLoaded = false;
	}

	bool Scene::IsLoaded() const
	{
		return m_IsLoaded;
	}

	void Scene::SceneStart()
	{
		for (auto& object : m_Objects)
		{
			object->SceneStart();
		}
	}

	void Scene::FixedUpdate()
	{
		for (auto& object : m_Objects)
		{
			object->FixedUpdate();
		}
	}

	void Scene::Update()
	{
		for (auto& object : m_Objects)
		{
			object->Update();
		}

		m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
			[](auto& object)
			{
				if (object->IsDestroyed())
				{
					object->OnDestroy();
					return true;
				}
				else return false;
			}
		), m_Objects.end());
	}

	void Scene::LateUpdate()
	{
		for (auto& object : m_Objects)
		{
			object->LateUpdate();
		}
	}

	void Scene::Render() const
	{
		for (const auto& object : m_Objects)
		{
			object->Render();
		}
	}

	void Scene::SceneEnd()
	{
		for (const auto& object : m_Objects)
		{
			object->SceneEnd();
		}
	}

	const std::string& Scene::GetName() const
	{
		return m_Name;
	}
}