#ifndef PLAYERDOWNCOMMAND_H
#define PLAYERDOWNCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerDownCommand final : public PlayerCommand
{
public:
	PlayerDownCommand(PlayerComponent* player)
		: PlayerCommand{ player }
	{
	}
	virtual ~PlayerDownCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveDown();
	}
};

#endif // !PLAYERDOWNCOMMAND_H