#ifndef PLAYERSTOPCOMMAND_H
#define	PLAYERSTOPCOMMAND_H

#include "PlayerCommand.h"

class PlayerStopCommand final : public PlayerCommand
{
public:

	explicit PlayerStopCommand(PlayerMovement* player, const glm::ivec2& dir)
		: PlayerCommand{ player }
		, m_Direcion{ dir }
	{
	}
	virtual ~PlayerStopCommand() = default;

	PlayerStopCommand(const PlayerStopCommand& other) = delete;
	PlayerStopCommand(PlayerStopCommand&& other) noexcept = delete;
	PlayerStopCommand& operator=(const PlayerStopCommand& other) = delete;
	PlayerStopCommand& operator=(PlayerStopCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		if (GetPlayer())
		{
			GetPlayer()->Stop(m_Direcion);
		}
	}

private:

	glm::ivec2 m_Direcion;

};

#endif // !PLAYERSTOPCOMMAND_H

