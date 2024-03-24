#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"

int PlayerComponent::s_playerCount{ 0 };

PlayerComponent::PlayerComponent(GameObject* const owner, float moveSpeed)
	: Component{ owner }
	, Subject{}
	, m_PlayerSpeed{ moveSpeed }
	, m_CurrentLives{ 3 }
	, m_Score{ 0 }
	, m_PlayerIdx{ s_playerCount++ }
{
}

void PlayerComponent::Move(const glm::vec3& dir)
{
	GetOwner()->Translate(dir * m_PlayerSpeed * Timer::Get().GetElapsedSec());
}

void PlayerComponent::Killed()
{
	m_CurrentLives -= 1;
	Notify(GetOwner(), GameEvent::playerDied);
}

void PlayerComponent::AddScore(int score)
{
	m_Score += score;
	Notify(GetOwner(), GameEvent::foundPickup);
}

int PlayerComponent::GetPlayerIdx() const
{
	return m_PlayerIdx;
}

int PlayerComponent::GetScore() const
{
	return m_Score;
}

int PlayerComponent::GetLives() const
{
	return m_CurrentLives;
}