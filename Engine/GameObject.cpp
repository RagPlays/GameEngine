#include <string>
#include "GameObject.h"

GameObject::GameObject(bool isStatic, const std::string& tag)
	: m_IsDestroyed{ false }
	, m_IsStatic{ isStatic }
	, m_Tag{ tag }
	, m_Transform{}
{
}

void GameObject::FixedUpdate()
{
	if (m_IsDestroyed) return;

	for (auto& component : m_Components)
	{
		component->FixedUpdate();
	}
}

void GameObject::Update()
{
	if (m_IsDestroyed) return;

	for (auto& component : m_Components)
	{
		component->Update();
	}
}

void GameObject::LateUpdate()
{
	if (m_IsDestroyed) return;

	for (auto& component : m_Components)
	{
		component->LateUpdate();
	}
}

void GameObject::Render() const
{
	if (m_IsDestroyed) return;

	for (const auto& component : m_Components)
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

template<typename ComponentType>
bool GameObject::HasComponent() const
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

// Get/Set Transform
const glm::vec3& GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

void GameObject::SetPosition(float x, float y, float z)
{
	if (m_IsStatic) return;
	m_Transform.SetPosition(x, y, z);
}

void GameObject::SetPosition(const glm::vec3& pos)
{
	if (m_IsStatic) return;
	m_Transform.SetPosition(pos.x, pos.y, pos.z);
}

void GameObject::SetPosition(float x, float y)
{
	if (m_IsStatic) return;
	m_Transform.SetPosition(x, y, 0.f);
}

void GameObject::SetPosition(const glm::vec2& pos)
{
	if (m_IsStatic) return;
	m_Transform.SetPosition(pos.x, pos.y, 0.f);
}

// Getters
bool GameObject::IsDestroyed() const
{
	return m_IsDestroyed;
}

bool GameObject::IsStatic() const
{
	return m_IsStatic;
}

const std::string& GameObject::GetTag() const
{
	return m_Tag;
}

// Setters
void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

// Other
bool GameObject::CompareTag(const std::string& tag)
{
	return m_Tag == tag;
}

void GameObject::Destroy()
{
	m_IsDestroyed = true;
}