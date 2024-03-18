#ifndef PLAYERRIGHTCOMMAND_H
#define PLAYERRIGHTCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerRightCommand final : public PlayerCommand
{
public:
	PlayerRightCommand(PlayerComponent* player)
		: PlayerCommand{ player }
	{
	}
	virtual ~PlayerRightCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveRight();
	}
};

#endif // !PLAYERRIGHTCOMMAND_H