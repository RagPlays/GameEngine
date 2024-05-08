#ifndef PLAYERCOMMAND_H
#define PLAYERCOMMAND_H

#include <glm.hpp>
#include "Command.h"
#include "PlayerMovementComponent.h"

class PlayerCommand : public Command
{
public:

	explicit PlayerCommand(PlayerMovementComponent* player)
		: m_Player{ player }
	{
	}
	virtual ~PlayerCommand() = default;

	PlayerCommand(const PlayerCommand& other) = delete;
	PlayerCommand(PlayerCommand&& other) noexcept = delete;
	PlayerCommand& operator=(const PlayerCommand& other) = delete;
	PlayerCommand& operator=(PlayerCommand&& other) noexcept = delete;

protected:

	PlayerMovementComponent* GetPlayer() { return m_Player; }

private:

	PlayerMovementComponent* m_Player;

};

#endif // !PLAYERCOMMAND_H