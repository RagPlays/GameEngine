#ifndef PLAYERLEFTCOMMAND_H
#define PLAYERLEFTCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerLeftCommand final : public PlayerCommand
{
public:
	PlayerLeftCommand(PlayerComponent* player)
		: PlayerCommand{ player }
	{
	}
	virtual ~PlayerLeftCommand() = default;

	virtual void Execute() override
	{
		GetPlayer()->MoveLeft();
	}
};


#endif // !PLAYERLEFTCOMMAND_H