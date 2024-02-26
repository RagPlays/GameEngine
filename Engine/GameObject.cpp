#include <string>
#include "GameObject.h"

GameObject::GameObject(bool isStatic, const std::string& tag)
	: m_IsStatic{ isStatic }
	, m_Tag{ tag }
	, m_Transform{}
{
}

void GameObject::FixedUpdate()
{
	for (auto& component : m_Components)
	{
		component->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_Components)
	{
		component->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (auto& component : m_Components)
	{
		component->Render();
	}
}

// Components
void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_Components.emplace_back(std::move(component));
}

void GameObject::RemoveComponent(std::shared_ptr<Component> component)
{
	m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
}

template <typename ComponentType>
std::shared_ptr<ComponentType> GameObject::GetComponent()
{
	for (auto& component : m_Components)
	{
		std::shared_ptr<ComponentType> castedComponent = std::dynamic_pointer_cast<ComponentType>(component);
		if (castedComponent)
		{
			return castedComponent;
		}
	}
	return nullptr;
}

template<typename ComponentType>
bool GameObject::HasComponent()
{
	for (auto& component : m_Components)
	{
		if (std::dynamic_pointer_cast<ComponentType>(component))
		{
			return true;
		}
	}
	return false;
}

// Getters
bool GameObject::IsStatic() const
{
	return m_IsStatic;
}

const std::string& GameObject::GetTag() const
{
	return m_Tag;
}

const Transform& GameObject::GetTransform() const
{
	return m_Transform;
}

// Setters
void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

void GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}

void GameObject::SetPosition(const glm::vec3& pos)
{
	m_Transform.SetPosition(pos.x, pos.y, pos.z);
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.f);
}

void GameObject::SetPosition(const glm::vec2& pos)
{
	m_Transform.SetPosition(pos.x, pos.y, 0.f);
}

// Other
bool GameObject::CompareTag(const std::string& tag)
{
	return m_Tag == tag;
}