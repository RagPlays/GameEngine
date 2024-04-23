#ifndef PLAYERCOMMAND_H
#define PLAYERCOMMAND_H

#include "Command.h"

class PlayerComponent;

class PlayerCommand : public Command
{
public:

	explicit PlayerCommand(PlayerComponent* player)
		: m_Player{ player }
	{
	}
	virtual ~PlayerCommand() = default;

	PlayerCommand(const PlayerCommand& other) = delete;
	PlayerCommand(PlayerCommand&& other) noexcept = delete;
	PlayerCommand& operator=(const PlayerCommand& other) = delete;
	PlayerCommand& operator=(PlayerCommand&& other) noexcept = delete;

protected:

	PlayerComponent* GetPlayer() { return m_Player; }

private:

	PlayerComponent* m_Player;
};

#endif // !PLAYERCOMMAND_H