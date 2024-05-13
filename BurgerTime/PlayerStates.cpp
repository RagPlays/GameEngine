#include <iostream>
#include <glm.hpp>

#include "PlayerStates.h"
#include "PlayerStateHandler.h"
#include "Player.h"
#include "PlayerMovement.h"

// Base Class
PlayerState::PlayerState(Player* const player, PlayerStateHandler* const handler)
	: State{}
	, m_pPlayer{ player }
	, m_pHandler{ handler }
{
}

void PlayerState::SetState(PlayerState* playerState)
{
	m_pHandler->SetState(playerState);
}

// IDLE //
PlayerIdleState::PlayerIdleState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerIdleState::OnEnter()
{
	// set srcRect
}

void PlayerIdleState::OnExit()
{
}

void PlayerIdleState::Update()
{
	/*const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	if (moveDir.x)
	{
		if (moveDir.x > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveLeftState());
		}
		else
		{
			m_pHandler->SetState(m_pHandler->GetMoveRightState());
		}
	}
	else if (moveDir.y)
	{
		if (moveDir.y > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveDownState());
		}
		else
		{
			m_pHandler->SetState(m_pHandler->GetMoveUpState());
		}
	}*/
}

// UP //
PlayerMoveUpState::PlayerMoveUpState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveUpState::OnEnter()
{
}

void PlayerMoveUpState::OnExit()
{
}

void PlayerMoveUpState::Update()
{
	//const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
}

// DOWN //
PlayerMoveDownState::PlayerMoveDownState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveDownState::OnEnter()
{
}

void PlayerMoveDownState::OnExit()
{
}

void PlayerMoveDownState::Update()
{
	//const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
}

// LEFT //
PlayerMoveLeftState::PlayerMoveLeftState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveLeftState::OnEnter()
{
}

void PlayerMoveLeftState::OnExit()
{
}

void PlayerMoveLeftState::Update()
{
	//const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
}

// RIGHT //
PlayerMoveRightState::PlayerMoveRightState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveRightState::OnEnter()
{
}

void PlayerMoveRightState::OnExit()
{
}

void PlayerMoveRightState::Update()
{
	//const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
}