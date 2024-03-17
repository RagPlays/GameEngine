#ifndef PLAYERRIGHTCOMMAND_H
#define PLAYERRIGHTCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerRightCommand final : PlayerCommand
{
public:
	PlayerRightCommand() = default;
	virtual ~PlayerRightCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveRight();
	}
};

#endif // !PLAYERRIGHTCOMMAND_H