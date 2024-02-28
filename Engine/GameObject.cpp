#include <string>
#include "GameObject.h"

GameObject::GameObject(bool isStatic, const std::string& tag)
	: m_PositionIsDirty{ true }
	, m_IsDestroyed{ false }
	, m_IsStatic{ isStatic }
	, m_Tag{ tag }
	, m_Transform{}
	, m_Parent{}
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
void GameObject::RemoveComponent(std::shared_ptr<Component> component)
{
	m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
}

// Childeren/Parent
bool GameObject::IsChild(GameObject* gameObj) const
{
	for (const GameObject* const child : m_Children)
	{
		if (child == gameObj) return true;
	}
	return false;
}

GameObject* GameObject::GetParent() const
{
	return m_Parent;
}

int GameObject::GetChildCount() const
{
	return static_cast<int>(m_Children.size());
}

GameObject* GameObject::GetChildAt(size_t idx) const
{
	assert(idx < m_Children.size());
	return m_Children[idx];
}

void GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	// TODO:: Make this complete
	if (IsChild(parent) || parent == this || m_Parent == parent) return;

	if (parent)
	{
		if (keepWorldPos)
		{
			// SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
			// SetPositionDirty
		}
	}
	else
	{
		// SetLocalPosition(GetWorldPosition());
	}

	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
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
	m_Transform.SetPosition(pos);
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

// Private functions
void GameObject::AddChild(GameObject* child)
{
	m_Children.emplace_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}

void GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_Parent)
		{
			// qmksjdfqsjdmfqs
		}
		else
		{
			
		}
	}
}