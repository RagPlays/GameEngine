#ifndef PLAYERKILLCOMMAND_H
#define PLAYERKILLCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerKillCommand final : public PlayerCommand
{
public:

	explicit PlayerKillCommand(PlayerComponent* player)
		: PlayerCommand{ player }
	{
	}
	virtual ~PlayerKillCommand() = default;

	PlayerKillCommand(const PlayerKillCommand& other) = delete;
	PlayerKillCommand(PlayerKillCommand&& other) noexcept = delete;
	PlayerKillCommand& operator=(const PlayerKillCommand& other) = delete;
	PlayerKillCommand& operator=(PlayerKillCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		GetPlayer()->Killed();
	}
};

#endif // !PLAYERKILLCOMMAND_H