#include "Component.h"

Component::Component(GameObject* const owner)
	: m_pOwner{ owner }
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

GameObject* const Component::GetOwner() const
{
	return m_pOwner;
}
