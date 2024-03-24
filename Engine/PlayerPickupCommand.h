#ifndef PLAYERPICKUPCOMMAND_H
#define PLAYERPICKUPCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerPickupCommand final : public PlayerCommand
{
public:

	explicit PlayerPickupCommand(PlayerComponent* player, int scoreOnPickup)
		: PlayerCommand{ player }
		, m_ScoreOnPickup{ scoreOnPickup }
	{
	}
	virtual ~PlayerPickupCommand() = default;

	PlayerPickupCommand(const PlayerPickupCommand& other) = delete;
	PlayerPickupCommand(PlayerPickupCommand&& other) noexcept = delete;
	PlayerPickupCommand& operator=(const PlayerPickupCommand& other) = delete;
	PlayerPickupCommand& operator=(PlayerPickupCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		GetPlayer()->AddScore(m_ScoreOnPickup);
	}
	
private:

	int m_ScoreOnPickup;
};

#endif // !PLAYERPICKUPCOMMAND_H

