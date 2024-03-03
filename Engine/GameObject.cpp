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
bool GameObject::IsChild(std::shared_ptr<GameObject> gameObj) const
{
	for (const std::shared_ptr<GameObject> child : m_Children)
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
	return m_Children[idx].get();
}

GameObject* GameObject::GetChildAt(int idx) const
{
	assert(idx < m_Children.size() && idx > -1);
	return m_Children[idx].get();
}

void GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
{
	if (parent.get() == this || m_Parent == parent.get() || IsChild(parent)) return;

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

	if (m_Parent) m_Parent->RemoveChild(std::make_shared<GameObject>(this));
	m_Parent = parent.get();
	if (m_Parent) m_Parent->AddChild(std::make_shared<GameObject>(this));
}

// Get/Set Transform
const glm::vec3& GameObject::GetLocalPosition() const
{
	return m_LocalTransform.GetPosition();
}

void GameObject::SetLocalPosition(float x, float y)
{
	if (m_IsStatic) return;
	SetLocalPosition({ x, y, 0.f });
}

void GameObject::SetLocalPosition(const glm::vec2& pos)
{
	if (m_IsStatic) return;
	SetLocalPosition({ pos.x, pos.y, 0.f });
}

void GameObject::SetLocalPosition(float x, float y, float z)
{
	if (m_IsStatic) return;
	SetLocalPosition({ x, y, z });
}

void GameObject::SetLocalPosition(const glm::vec3& pos)
{
	if (m_IsStatic) return;
	m_LocalTransform.SetPosition(pos);
	m_PositionIsDirty = true;
}

const glm::vec3& GameObject::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_WorldTransform.GetPosition();
}

void GameObject::SetWorldPosition(float x, float y, float z)
{
	m_WorldTransform.SetPosition(x, y, z);
}

void GameObject::SetWorldPosition(const glm::vec3& pos)
{
	m_WorldTransform.SetPosition(pos);
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
void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_Children.emplace_back(child);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}

void GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
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
}