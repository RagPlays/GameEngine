#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"

PlayerComponent::PlayerComponent(GameObject* const owner, float moveSpeed)
	: Component{ owner }
	, m_PlayerSpeed{ moveSpeed }
{
}

void PlayerComponent::MoveUp()
{
	GetOwner()->Translate({ 0.f, -m_PlayerSpeed * Timer::Get().GetElapsedSec(), 0.f });
}

void PlayerComponent::MoveDown()
{
	GetOwner()->Translate({ 0.f, m_PlayerSpeed * Timer::Get().GetElapsedSec(), 0.f });
}

void PlayerComponent::MoveLeft()
{
	GetOwner()->Translate({ -m_PlayerSpeed * Timer::Get().GetElapsedSec(), 0.f, 0.f });
}

void PlayerComponent::MoveRight()
{
	GetOwner()->Translate({ m_PlayerSpeed * Timer::Get().GetElapsedSec(), 0.f, 0.f });
}