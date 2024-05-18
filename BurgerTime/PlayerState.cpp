#include "PlayerState.h"
#include "Player.h"
#include "PlayerStateHandler.h"

PlayerState::PlayerState(Player* const player, PlayerStateHandler* const handler)
	: State{}
	, m_pPlayer{ player }
	, m_pHandler{ handler }
{
}