#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"

PlayerComponent::PlayerComponent(GameObject* const owner, float moveSpeed)
	: Component{ owner }
	, m_PlayerSpeed{ moveSpeed }
{
}

void PlayerComponent::Move(const glm::vec3& dir)
{
	GetOwner()->Translate(dir * m_PlayerSpeed * Timer::Get().GetElapsedSec());
}
