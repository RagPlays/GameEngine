#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"

int PlayerComponent::s_playerCount{ 0 };

PlayerComponent::PlayerComponent(GameObject* const owner, float moveSpeed)
	: Component{ owner }
	, Subject{}
	, m_PlayerSpeed{ moveSpeed }
	, m_PlayerIdx{ s_playerCount++ }
{
}

void PlayerComponent::GameStart()
{
	Notify(GetOwner(), GameEvent::playerJoined);
}

void PlayerComponent::Move(const glm::vec3& dir)
{
	GetOwner()->Translate(dir * m_PlayerSpeed * Timer::Get().GetElapsedSec());
}

void PlayerComponent::Killed()
{
	Notify(GetOwner(), GameEvent::playerDied);
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
	default:
		break;
	}
}

int PlayerComponent::GetPlayerIdx() const
{
	return m_PlayerIdx;
}