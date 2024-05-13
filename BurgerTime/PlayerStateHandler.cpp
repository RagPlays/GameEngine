#include "PlayerStateHandler.h"
#include "PlayerStates.h"

PlayerStateHandler::PlayerStateHandler(Player* const player)
	: m_IdleState{ std::make_unique<PlayerIdleState>(player, this) }
	, m_MoveUpState{ std::make_unique<PlayerMoveUpState>(player, this) }
	, m_MoveDownState{ std::make_unique<PlayerMoveDownState>(player, this) }
	, m_MoveLeftState{ std::make_unique<PlayerMoveLeftState>(player, this) }
	, m_MoveRightState{ std::make_unique<PlayerMoveRightState>(player, this) }
	, m_pCurrentState{ nullptr }
{
}

PlayerStateHandler::~PlayerStateHandler() = default;

void PlayerStateHandler::SetState(PlayerState* playerState)
{
	if (!playerState || m_pCurrentState == playerState) return;
	if (m_pCurrentState)
	{
		m_pCurrentState->OnExit();
	}
	m_pCurrentState = playerState;
	m_pCurrentState->OnEnter();
}

void PlayerStateHandler::Update()
{
	if(m_pCurrentState) m_pCurrentState->Update();
}

void PlayerStateHandler::SceneStart()
{
	if (m_pCurrentState)
	{
		// This should not happen
		m_pCurrentState->OnExit();
	}
	m_pCurrentState = m_IdleState.get();
	m_pCurrentState->OnEnter();
}

PlayerIdleState* PlayerStateHandler::GetIdleState() const
{
	return m_IdleState.get();
}

PlayerMoveUpState* PlayerStateHandler::GetMoveUpState() const
{
	return m_MoveUpState.get();
}

PlayerMoveDownState* PlayerStateHandler::GetMoveDownState() const
{
	return m_MoveDownState.get();
}

PlayerMoveLeftState* PlayerStateHandler::GetMoveLeftState() const
{
	return m_MoveLeftState.get();
}

PlayerMoveRightState* PlayerStateHandler::GetMoveRightState() const
{
	return m_MoveRightState.get();
}