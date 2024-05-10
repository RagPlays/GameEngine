#ifndef PLAYERCOMMAND_H
#define PLAYERCOMMAND_H

#include "Command.h"

class PlayerMovement;

class PlayerCommand : public Command
{
public:

	explicit PlayerCommand(PlayerMovement* player)
		: m_pPlayer{ player }
	{
	}
	virtual ~PlayerCommand() = default;

	PlayerCommand(const PlayerCommand& other) = delete;
	PlayerCommand(PlayerCommand&& other) noexcept = delete;
	PlayerCommand& operator=(const PlayerCommand& other) = delete;
	PlayerCommand& operator=(PlayerCommand&& other) noexcept = delete;

protected:

	PlayerMovement* GetPlayer()
	{
		return m_pPlayer;
	}

private:

	PlayerMovement* m_pPlayer;

};

#endif // !PLAYERCOMMAND_H