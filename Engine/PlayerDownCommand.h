#ifndef PLAYERDOWNCOMMAND_H
#define PLAYERDOWNCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerDownCommand final : PlayerCommand
{
public:
	PlayerDownCommand() = default;
	virtual ~PlayerDownCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveDown();
	}
};

#endif // !PLAYERDOWNCOMMAND_H