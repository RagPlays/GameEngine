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
}