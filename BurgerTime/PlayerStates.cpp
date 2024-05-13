#include "PlayerStates.h"

std::unique_ptr<PlayerState> PlayerState::m_IdleState{ std::make_unique<PlayerIdleState>() };
std::unique_ptr<PlayerState> PlayerState::m_MoveUpState{ std::make_unique<PlayerMoveUpState>() };
std::unique_ptr<PlayerState> PlayerState::m_MoveDownState{ std::make_unique<PlayerMoveDownState>() };
std::unique_ptr<PlayerState> PlayerState::m_MoveLeftState{ std::make_unique<PlayerMoveLeftState>() };
std::unique_ptr<PlayerState> PlayerState::m_MoveRightState{ std::make_unique<PlayerMoveRightState>() };

// IDLE //
void PlayerIdleState::OnEnter()
{
}

void PlayerIdleState::OnExit()
{
}

void PlayerIdleState::Update(Player* const)
{
}


// UP //
void PlayerMoveUpState::OnEnter()
{
}

void PlayerMoveUpState::OnExit()
{
}

void PlayerMoveUpState::Update(Player* const)
{
}

// DOWN //
void PlayerMoveDownState::OnEnter()
{
}

void PlayerMoveDownState::OnExit()
{
}

void PlayerMoveDownState::Update(Player* const)
{
}

// LEFT //
void PlayerMoveLeftState::OnEnter()
{
}

void PlayerMoveLeftState::OnExit()
{
}

void PlayerMoveLeftState::Update(Player* const)
{
}

// RIGHT //
void PlayerMoveRightState::OnEnter()
{
}

void PlayerMoveRightState::OnExit()
{
}

void PlayerMoveRightState::Update(Player* const)
{
}