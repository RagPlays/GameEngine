#ifndef PLAYERUPCOMMAND_H
#define PLAYERUPCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerUpCommand final : public PlayerCommand
{
public:
	PlayerUpCommand(PlayerComponent* player)
		: PlayerCommand{ player }
	{
	}
	virtual ~PlayerUpCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveUp();
	}
};

#endif // !PLAYERUPCOMMAND_H