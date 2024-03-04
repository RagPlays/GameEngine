#include "GameObject.h"

GameObject::GameObject(bool isStatic, const std::string& tag)
	: m_PositionIsDirty{ true }
	, m_IsDestroyed{ false }
	, m_IsStatic{ isStatic }
	, m_Tag{ tag }
	, m_LocalTransform{}
	, m_WorldTransform{}
	, m_Components{}
	, m_Children{}
	, m_Parent{}
{
	m_Components.clear();
	m_Children.clear();
}

void GameObject::FixedUpdate()
{
	if (m_IsDestroyed) return;

	for (auto& component : m_Components)
	{
		component->FixedUpdate();
	}

	for (auto& child : m_Children)
	{
		child->FixedUpdate();
	}
}

void GameObject::Update()
{
	if (m_IsDestroyed) return;

	for (auto& component : m_Components)
	{
		component->Update();
	}

	for (auto& child : m_Children)
	{
		child->Update();
	}
}

void GameObject::LateUpdate()
{
	if (m_IsDestroyed) return;

	for (auto& component : m_Components)
	{
		component->LateUpdate();
	}

	for (auto& child : m_Children)
	{
		child->LateUpdate();
	}
}

void GameObject::Render() const
{
	if (m_IsDestroyed) return;

	for (const auto& component : m_Components)
	{
		component->Render();
	}

	for (const auto& child : m_Children)
	{
		child->Render();
	}
}

// Childeren/Parent
bool GameObject::IsChild(GameObject* gameObj) const
{
	for (const auto& child : m_Children) 
	{
		if (child.get() == gameObj) return true;
	}
	return false;
}

GameObject* GameObject::GetParent() const
{
	return m_Parent;
}

size_t GameObject::GetChildCount() const
{
	return m_Children.size();
}

GameObject* GameObject::GetChildAt(size_t idx) const
{
	assert(idx < m_Children.size());
	return m_Children[idx].get();
}

const std::vector<std::unique_ptr<GameObject>>& GameObject::GetChilderen() const
{
	return m_Children;
}

void GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (parent == this || m_Parent == parent || IsChild(parent)) return;

	if (parent)
	{
		if (keepWorldPos)
		{
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		}
		m_PositionIsDirty = true;
	}
	else
	{
		SetLocalPosition(GetWorldPosition());
	}

	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

// Get/Set Transform
const glm::vec3& GameObject::GetLocalPosition() const
{
	return m_LocalTransform.GetPosition();
}

void GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalTransform.SetPosition(pos);
	m_PositionIsDirty = true;
}

const glm::vec3& GameObject::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_WorldTransform.GetPosition();
}

// Getters
bool GameObject::IsDestroyed() const
{
	return m_IsDestroyed;
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
	for (auto& child : m_Children)
	{
		child->Destroy();
	}
}

// Private functions
void GameObject::AddChild(GameObject* child)
{
	m_Children.emplace_back(std::unique_ptr<GameObject>(child));
}

void GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(),[&](const std::unique_ptr<GameObject>& ptr)
		{ 
			return ptr.get() == child; 
		}
	), m_Children.end());
}

void GameObject::UpdateWorldPosition()
{
	if (!m_PositionIsDirty) return;

	if (m_Parent)
	{
		m_WorldTransform.SetPosition(m_Parent->GetWorldPosition() + m_LocalTransform.GetPosition());
	}
	else
	{
		m_WorldTransform.SetPosition(m_LocalTransform.GetPosition());
	}

	m_PositionIsDirty = false;
}