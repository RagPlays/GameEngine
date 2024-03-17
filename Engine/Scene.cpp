#include "Scene.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
{
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
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

	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),[](auto& object)
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

void Scene::RemoveAllObjects()
{
	m_Objects.clear();
}