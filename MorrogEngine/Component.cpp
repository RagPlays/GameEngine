#include "Component.h"
#include "GameObject.h"

namespace MoE
{
	Component::Component(GameObject* const owner)
		: m_pOwner{ owner }
	{
	}

	void Component::SceneStart()
	{
	}

	void Component::FixedUpdate()
	{
	}

	void Component::Update()
	{
	}

	void Component::LateUpdate()
	{
	}

	void Component::Render() const
	{
	}

	void Component::OnDestroy()
	{
	}

	void Component::SceneEnd()
	{
	}

	// Gets
	GameObject* const Component::GetOwner() const
	{
		return m_pOwner;
	}

	GameObject* const Component::GetParent() const
	{
		return m_pOwner->GetParent();
	}

	const glm::vec2& Component::GetLocalPosition() const
	{
		return m_pOwner->GetLocalPosition();
	}

	const glm::vec2& Component::GetWorldPosition() const
	{
		return m_pOwner->GetWorldPosition();
	}

	// Sets
	void Component::SetLocalPosition(const glm::vec2& pos)
	{
		m_pOwner->SetLocalPosition(pos);
	}
}