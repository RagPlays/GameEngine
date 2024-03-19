#ifndef PLAYERMOVECOMMAND_H
#define PLAYERMOVECOMMAND_H

#include <glm.hpp>
#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerMoveCommand final : public PlayerCommand
{
public:

	explicit PlayerMoveCommand(PlayerComponent* player, const glm::vec3& dir)
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
		GetPlayer()->Move(m_Direcion);
	}

private:

	glm::vec3 m_Direcion;

};

#endif // !PLAYERMOVECOMMAND_H
