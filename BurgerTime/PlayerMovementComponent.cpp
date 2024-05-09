#include <iostream>
#include "PlayerMovementComponent.h"
#include "Timer.h"
#include "GameObject.h"

PlayerMovementComponent::PlayerMovementComponent(GameObject* const owner, float movementSpeed)
	: Component{ owner }
	, m_PlayerSpeed{ movementSpeed }
	, m_MovementDir{ glm::ivec2{} }
{
}

void PlayerMovementComponent::FixedUpdate()
{
	/*if (*m_pLevel == nullptr)
	{
		std::cout << "level is destroyyyyyyyyed!!\n";
	}
	else
	{
		std::cout << "level still existsssssssss!!\n";
	}*/
	const float fixedTime{ Timer::Get().GetFixedElapsedSec() };
	const float moveScale{ m_PlayerSpeed * fixedTime };
	const glm::vec2 tranlation{ static_cast<glm::vec2>(m_MovementDir) * moveScale };
	GetOwner()->Translate(tranlation);
}

void PlayerMovementComponent::Move(const glm::ivec2& dir)
{
	m_MovementDir = dir;
}

void PlayerMovementComponent::Stop(const glm::ivec2& dir)
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

void PlayerMovementComponent::SetPosition(const glm::ivec2& pos)
{
	GetOwner()->SetLocalPosition(static_cast<glm::vec2>(pos));
}