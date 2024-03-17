#ifndef PLAYERCOMMAND_H
#define PLAYERCOMMAND_H

#include "Command.h"

class PlayerComponent;

class PlayerCommand : public Command
{
public:

	PlayerCommand(PlayerComponent* player)
		: m_Player{ player }
	{
	}
	virtual ~PlayerCommand() = default;

protected:

	PlayerComponent* GetPlayer() { return m_Player; }

private:

	PlayerComponent* m_Player;
};

#endif // !PLAYERCOMMAND_H