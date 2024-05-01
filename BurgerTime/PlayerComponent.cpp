#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "EventQueue.h"

unsigned int PlayerComponent::s_PlayerCount{ 0 };

PlayerComponent::PlayerComponent(GameObject* const owner, float moveSpeed)
	: Component{ owner }
	, Subject{}
	, m_MovementDir{}
	, m_PlayerSpeed{ moveSpeed }
	, m_PlayerIdx{ s_PlayerCount++ }
{
}

PlayerComponent::~PlayerComponent()
{
	--s_PlayerCount;
}

void PlayerComponent::GameStart()
{
	Notify(GetOwner(), GameEvent::playerJoined);
}

void PlayerComponent::FixedUpdate()
{
	GameObject* const owner{ GetOwner() };
	const float fixedTime{ Timer::Get().GetFixedElapsedSec() };
	const float moveScale{ m_PlayerSpeed * fixedTime };
	
	if (m_MovementDir.y)
	{
		owner->Translate(glm::vec2{ 0.f, m_MovementDir.y * moveScale });
	}
	else if (m_MovementDir.x)
	{
		owner->Translate(glm::vec2{ m_MovementDir.x * moveScale, 0.f });
	}
}

void PlayerComponent::Move(const glm::ivec2& dir)
{
	m_MovementDir = dir;
}

void PlayerComponent::Stop(const glm::ivec2& stopDir)
{
	if (stopDir.y > 0 && m_MovementDir.y > 0)
	{
		m_MovementDir.y = 0;
	}
	else if (stopDir.y < 0 && m_MovementDir.y < 0)
	{
		m_MovementDir.y = 0;
	}
	else if (stopDir.x > 0 && m_MovementDir.x > 0)
	{
		m_MovementDir.x = 0;
	}
	else if (stopDir.x < 0 && m_MovementDir.x < 0)
	{
		m_MovementDir.x = 0;
	}
}

void PlayerComponent::Killed()
{
	Notify(GetOwner(), GameEvent::playerDied);
	EventQueue::Get().AddEvent(GameEvent::playerDied);
}

void PlayerComponent::PickupEvent(PickupItem item)
{
	switch (item)
	{
	case PickupItem::smallItem:
		Notify(GetOwner(), GameEvent::foundSmallPickup);
		break;
	case PickupItem::bigItem:
		Notify(GetOwner(), GameEvent::foundLargePickup);
		break;
	}
}

int PlayerComponent::GetPlayerIdx() const
{
	return m_PlayerIdx;
}