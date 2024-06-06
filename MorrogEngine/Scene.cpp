#include <vector>

#include "Scene.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "InputManager.h"
#include "EventQueue.h"

namespace MoE
{
	Scene::Scene(const std::string& name, std::function<void(Scene&)>&& loadFunc)
		: m_IsLoaded{}
		, m_LoadFunction{ std::move(loadFunc) }
		, m_Name{ name }
		, m_RootObject{ std::make_unique<GameObject>() }
	{
	}

	Scene::~Scene()
	{
		UnLoad();
	}

	void Scene::Add(std::unique_ptr<GameObject>&& object)
	{
		object->SetParent(m_RootObject.get());
		object.release(); // can be released because ownership is transfered to the parent gameObject
	}

	void Scene::Load()
	{
		m_LoadFunction(*this);
		m_IsLoaded = true;
	}

	void Scene::UnLoad()
	{
		if (!m_IsLoaded) return;
		// Unload GameObjects
		m_RootObject.reset();
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
		m_RootObject->SceneStart();
	}

	void Scene::FixedUpdate()
	{
		m_RootObject->FixedUpdate();
	}

	void Scene::Update()
	{
		m_RootObject->Update();
	}

	void Scene::LateUpdate()
	{
		m_RootObject->LateUpdate();

		CheckDeletions();
	}

	void Scene::Render() const
	{
		m_RootObject->Render();
	}

	void Scene::SceneEnd()
	{
		m_RootObject->SceneEnd();
	}

	const std::string& Scene::GetName() const
	{
		return m_Name;
	}

	void Scene::CheckDeletions()
	{
		m_RootObject->DeleteDestroyed();
	}
}