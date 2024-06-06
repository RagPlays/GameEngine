#include "GameObject.h"
#include "Component.h"

namespace MoE
{
	GameObject::GameObject()
		: m_LocalTransform{}
		, m_WorldTransform{}
		, m_Components{}
		, m_Children{}
		, m_Parent{}
		, m_PositionIsDirty{}
		, m_IsDestroyed{}
	{
		m_Components.clear();
		m_Children.clear();
	}

	GameObject::~GameObject()
	{
		m_Components.clear();
		m_Children.clear();
	}

	void GameObject::SceneStart()
	{
		for (auto& component : m_Components)
		{
			component->SceneStart();
		}

		for (auto& child : m_Children)
		{
			child->SceneStart();
		}
	}

	void GameObject::FixedUpdate()
	{
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
		for (const auto& component : m_Components)
		{
			component->Render();
		}

		for (const auto& child : m_Children)
		{
			child->Render();
		}
	}

	void GameObject::OnDestroy()
	{
		for (auto& component : m_Components)
		{
			component->OnDestroy();
		}

		for (auto& child : m_Children)
		{
			child->OnDestroy();
		}
	}

	void GameObject::SceneEnd()
	{
		for (auto& component : m_Components)
		{
			component->SceneEnd();
		}

		for (auto& child : m_Children)
		{
			child->SceneEnd();
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
			SetPositionDirty();
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
	const glm::vec2& GameObject::GetLocalPosition() const
	{
		return m_LocalTransform.GetPosition();
	}

	void GameObject::SetLocalPosition(const glm::vec2& pos)
	{
		m_LocalTransform.SetPosition(pos);
		SetPositionDirty();
	}

	const glm::vec2& GameObject::GetWorldPosition()
	{
		UpdateWorldPosition();
		return m_WorldTransform.GetPosition();
	}

	void GameObject::SetWorldPosition(const glm::vec2& pos)
	{
		if (m_Parent)
		{
			SetLocalPosition(pos - m_Parent->GetWorldPosition());
			return;
		}
		SetLocalPosition(pos);
	}

	void GameObject::SetPositionDirty()
	{
		m_PositionIsDirty = true;
		for (auto& child : m_Children)
		{
			child->SetPositionDirty();
		}
	}

	void GameObject::Translate(const glm::vec2& translate)
	{
		SetLocalPosition(GetLocalPosition() + translate);
	}

	// Getters
	bool GameObject::IsDestroyed() const
	{
		return m_IsDestroyed;
	}

	void GameObject::DeleteDestroyed()
	{
		for (auto it{ m_Children.rbegin() }; it != m_Children.rend();)
		{
			if ((*it)->IsDestroyed())
			{
				it = decltype(it)(m_Children.erase(std::next(it).base()));
			}
			else ++it;
		}

		for (auto& child : m_Children) child->DeleteDestroyed();
	}

	void GameObject::Destroy()
	{
		m_IsDestroyed = true;
		for (auto& child : m_Children)
		{
			child->Destroy();
		}
	}

	void GameObject::Destroy(GameObject* gameObj)
	{
		gameObj->Destroy();
	}

	// Private functions
	void GameObject::AddChild(GameObject* child)
	{
		m_Children.emplace_back(std::move(child));
	}

	void GameObject::RemoveChild(GameObject* child)
	{
		m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(),
			[child](auto& ptr)
			{
				return ptr.get() == child;
			}
		), m_Children.end());
	}

	void GameObject::UpdateWorldPosition()
	{
		if (!m_PositionIsDirty) return;
		m_PositionIsDirty = false;

		if (m_Parent)
		{
			m_WorldTransform.SetPosition(m_Parent->GetWorldPosition() + m_LocalTransform.GetPosition());
			return;
		}
		m_WorldTransform.SetPosition(m_LocalTransform.GetPosition());
	}
}