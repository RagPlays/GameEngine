#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "EventQueue.h"

unsigned int PlayerComponent::s_PlayerCount{ 0 };

PlayerComponent::PlayerComponent(GameObject* const owner, float moveSpeed)
	: Component{ owner }
	, Subject{}
	, m_PlayerIdx{ s_PlayerCount++ }
	, m_PlayerSpeed{ moveSpeed }
	, m_MovementDir{}
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
	const glm::vec2 tranlation{ static_cast<glm::vec2>(m_MovementDir) * moveScale };

	owner->Translate(tranlation);
}

void PlayerComponent::Move(const glm::ivec2& dir)
{
	m_MovementDir = dir;
}

void PlayerComponent::Stop(const glm::ivec2& dir)
{
	if ((dir.y > 0 && m_MovementDir.y > 0) || (dir.y < 0 && m_MovementDir.y < 0))
	{
		m_MovementDir.y = 0;
	}
	else if ((dir.x > 0 && m_MovementDir.x > 0) || (dir.x < 0 && m_MovementDir.x < 0))
	{
		m_MovementDir.x = 0;
	}
}

void PlayerComponent::FullStop()
{
	m_MovementDir = glm::vec2{};
}

void PlayerComponent::Killed()
{
	Notify(GetOwner(), GameEvent::playerDied);
	EventQueue::Get().AddEvent(GameEvent::playerDied);
}

int PlayerComponent::GetPlayerIdx() const
{
	return m_PlayerIdx;
}