#include <iostream>

#include "PlayerMovement.h"
#include "RenderComponent.h"
#include "Timer.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "LevelCollision.h"
#include "GameManager.h"
#include "LevelManager.h"

using namespace MoE;

PlayerMovement::PlayerMovement(GameObject* const owner)
	: Component{ owner }
	, m_PlayerSpeed{ 42, 22 }
	, m_MovementDir{}
	, m_HitBoxSize{}
{
	const int tileSize{ LevelManager::Get().GetTileSize() };
	const int gameScale{ GameManager::Get().GetGameScale() };
	m_PlayerSpeed *= gameScale;
	m_HitBoxSize = glm::ivec2{ gameScale * tileSize, gameScale * tileSize };
}

void PlayerMovement::GameStart()
{
	if (RenderComponent* const renderComp{ GetOwner()->GetComponent<RenderComponent>() })
	{
		renderComp->SetTextureDimensions(m_HitBoxSize);
	}
	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		GetOwner()->SetLocalPosition(coll->GetStartPos());
	}
}

void PlayerMovement::FixedUpdate()
{
	if (!m_MovementDir.x && !m_MovementDir.y) return;

	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		GameObject* owner{ GetOwner() };
		const float fixedTime{ Timer::Get().GetFixedElapsedSec() };
		const glm::vec2 moveScale{ static_cast<glm::vec2>(m_PlayerSpeed) * fixedTime };
		const glm::vec2 translation{ static_cast<glm::vec2>(m_MovementDir) * moveScale };
		const glm::vec2 originalPos{ owner->GetLocalPosition() };

		owner->Translate(translation);

		if (!coll->CanMove(this))
		{
			owner->SetLocalPosition(originalPos);
		}
	}
}

const glm::ivec2& PlayerMovement::GetHitBox() const
{
	return m_HitBoxSize;
}

const glm::ivec2& PlayerMovement::GetMoveDir() const
{
	return m_MovementDir;
}

const glm::vec2& PlayerMovement::GetPosition() const
{
	return GetOwner()->GetLocalPosition();
}

void PlayerMovement::SetPosition(const glm::vec2& pos)
{
	GetOwner()->SetLocalPosition(pos);
}

void PlayerMovement::Move(const glm::ivec2& dir)
{
	m_MovementDir = dir;
}

void PlayerMovement::Stop(const glm::ivec2& dir)
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

void PlayerMovement::SetPosition(const glm::ivec2& pos)
{
	GetOwner()->SetLocalPosition(static_cast<glm::vec2>(pos));
}