#ifndef PLAYERLEFTCOMMAND_H
#define PLAYERLEFTCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerLeftCommand final : PlayerCommand
{
public:
	PlayerLeftCommand() = default;
	virtual ~PlayerLeftCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveLeft();
	}
};

#endif // !PLAYERLEFTCOMMAND_H