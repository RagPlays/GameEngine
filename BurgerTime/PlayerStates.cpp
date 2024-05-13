#include <iostream>
#include <glm.hpp>

#include "PlayerStates.h"
#include "PlayerStateHandler.h"
#include "Player.h"
#include "PlayerMovement.h"
#include "RenderComponent.h"

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
	/*if (MoE::RenderComponent* const renderComp{ m_pPlayer->GetRenderComponent() })
	{
		renderComp->SetSourceRect(16, 0, 16, 16);
	}*/
}

void PlayerIdleState::OnExit()
{
}

void PlayerIdleState::Update()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	if (moveDir.x)
	{
		if (moveDir.x > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveRightState());
		}
		else
		{
			m_pHandler->SetState(m_pHandler->GetMoveLeftState());
		}
	}
	else if(moveDir.y)
	{
		if (moveDir.y > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveDownState());
		}
		else
		{
			m_pHandler->SetState(m_pHandler->GetMoveUpState());
		}
	}
	/*const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	std::unordered_map<glm::ivec2, std::function<void()>> directionToStateMap
	{
		{ glm::ivec2{ 1,  0 },[&]() { m_pHandler->SetState(m_pHandler->GetMoveLeftState());  } },
		{ glm::ivec2{ -1, 0 },[&]() { m_pHandler->SetState(m_pHandler->GetMoveRightState()); } },
		{ glm::ivec2{ 0,  1 },[&]() { m_pHandler->SetState(m_pHandler->GetMoveDownState());  } },
		{ glm::ivec2{ 0, -1 },[&]() { m_pHandler->SetState(m_pHandler->GetMoveUpState());	 } }
	};

	if (directionToStateMap.count(moveDir))
	{
		directionToStateMap[moveDir]();
	}*/
}

// UP //
PlayerMoveUpState::PlayerMoveUpState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveUpState::OnEnter()
{
	if (MoE::RenderComponent* const renderComp{ m_pPlayer->GetRenderComponent() })
	{
		renderComp->SetSourceRect(16, 16, 16, 16);
	}
}

void PlayerMoveUpState::OnExit()
{
}

void PlayerMoveUpState::Update()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	if (moveDir.y)
	{
		if (moveDir.y > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveDownState());
		}
	}
	else if (moveDir.x)
	{
		if (moveDir.x > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveRightState());
		}
		else
		{
			m_pHandler->SetState(m_pHandler->GetMoveLeftState());
		}
	}
	else
	{
		m_pHandler->SetState(m_pHandler->GetIdleState());
	}
}

// DOWN //
PlayerMoveDownState::PlayerMoveDownState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveDownState::OnEnter()
{
	if (MoE::RenderComponent* const renderComp{ m_pPlayer->GetRenderComponent() })
	{
		renderComp->SetSourceRect(16, 0, 16, 16);
	}
}

void PlayerMoveDownState::OnExit()
{
}

void PlayerMoveDownState::Update()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	if (moveDir.y)
	{
		if (moveDir.y < 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveUpState());
		}
	}
	else if (moveDir.x)
	{
		if (moveDir.x > 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveRightState());
		}
		else
		{
			m_pHandler->SetState(m_pHandler->GetMoveLeftState());
		}
	}
	else
	{
		m_pHandler->SetState(m_pHandler->GetIdleState());
	}
}

// LEFT //
PlayerMoveLeftState::PlayerMoveLeftState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveLeftState::OnEnter()
{
	if (MoE::RenderComponent* const renderComp{ m_pPlayer->GetRenderComponent() })
	{
		renderComp->SetSourceRect(16, 32, 16, 16);
	}
}

void PlayerMoveLeftState::OnExit()
{
}

void PlayerMoveLeftState::Update()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	if (moveDir.x)
	{
		if (moveDir.x > 0)
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
	}
	else
	{
		m_pHandler->SetState(m_pHandler->GetIdleState());
	}
}

// RIGHT //
PlayerMoveRightState::PlayerMoveRightState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerMoveRightState::OnEnter()
{
	if (MoE::RenderComponent* const renderComp{ m_pPlayer->GetRenderComponent() })
	{
		renderComp->SetSourceRect(16, 32, 16, 16);
	}
	// flip rendering // !!!!
}

void PlayerMoveRightState::OnExit()
{
}

void PlayerMoveRightState::Update()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMovementComponent()->GetMoveDir() };
	if (moveDir.x)
	{
		if (moveDir.x < 0)
		{
			m_pHandler->SetState(m_pHandler->GetMoveLeftState());
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
	}
	else
	{
		m_pHandler->SetState(m_pHandler->GetIdleState());
	}
}