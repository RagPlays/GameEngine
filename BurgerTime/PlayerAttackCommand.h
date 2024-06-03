#ifndef PLAYERATTACKCOMMAND_H
#define PLAYERATTACKCOMMAND_H

#include "PlayerCommand.h"
#include "Player.h"

class PlayerAttackCommand final : public PlayerCommand
{
public:

	explicit PlayerAttackCommand(Player* const player)
		: PlayerCommand{ player }
	{
	}
	virtual ~PlayerAttackCommand() = default;

	virtual void Execute()
	{
		if (!GetPlayer()->IsAttacking())
		{
			GetPlayer()->SetAttacking(true);
		}
	}
};

#endif // !PLAYERATTACKCOMMAND_H
