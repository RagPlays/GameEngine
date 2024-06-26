#ifndef PLAYERMOVECOMMAND_H
#define PLAYERMOVECOMMAND_H

#include "PlayerCommand.h"

#include "Player.h"

class PlayerMoveCommand final : public PlayerCommand
{
public:

	explicit PlayerMoveCommand(Player* const player, const glm::ivec2& dir)
		: PlayerCommand{ player }
		, m_Direcion{ dir }
	{
	}
	virtual ~PlayerMoveCommand() = default;

	PlayerMoveCommand(const PlayerMoveCommand& other) = delete;
	PlayerMoveCommand(PlayerMoveCommand&& other) noexcept = delete;
	PlayerMoveCommand& operator=(const PlayerMoveCommand& other) = delete;
	PlayerMoveCommand& operator=(PlayerMoveCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		if (GetPlayer())
		{
			GetPlayer()->Move(m_Direcion);
		}
	}

private:

	const glm::ivec2 m_Direcion;

};

#endif // !PLAYERMOVECOMMAND_H
