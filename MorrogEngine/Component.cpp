#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* const owner)
	: m_pOwner{ owner }
{
}

void Component::GameStart()
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

// Gets
GameObject* const Component::GetOwner() const
{
	return m_pOwner;
}

GameObject* Component::GetParent() const
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