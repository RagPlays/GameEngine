#ifndef PLAYERCOMMAND_H
#define PLAYERCOMMAND_H

#include "Command.h"

class Player;

class PlayerCommand : public MoE::Command
{
public:

	explicit PlayerCommand(Player* player)
		: m_pPlayer{ player }
	{
	}
	virtual ~PlayerCommand() = default;

	PlayerCommand(const PlayerCommand& other) = delete;
	PlayerCommand(PlayerCommand&& other) noexcept = delete;
	PlayerCommand& operator=(const PlayerCommand& other) = delete;
	PlayerCommand& operator=(PlayerCommand&& other) noexcept = delete;

protected:

	Player* GetPlayer()
	{
		return m_pPlayer;
	}

private:

	Player* m_pPlayer;

};

#endif // !PLAYERCOMMAND_H