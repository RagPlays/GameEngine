#ifndef PLAYERPICKUPCOMMAND_H
#define PLAYERPICKUPCOMMAND_H

#include "PlayerCommand.h"
#include "PlayerComponent.h"

class PlayerPickupCommand final : public PlayerCommand
{
public:

	explicit PlayerPickupCommand(PlayerComponent* player, PickupItem pickupItem)
		: PlayerCommand{ player }
		, m_PickupItem{ pickupItem }
	{
	}
	virtual ~PlayerPickupCommand() = default;

	PlayerPickupCommand(const PlayerPickupCommand& other) = delete;
	PlayerPickupCommand(PlayerPickupCommand&& other) noexcept = delete;
	PlayerPickupCommand& operator=(const PlayerPickupCommand& other) = delete;
	PlayerPickupCommand& operator=(PlayerPickupCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		GetPlayer()->PickupEvent(m_PickupItem);
	}
	
private:

	PickupItem m_PickupItem;
};

#endif // !PLAYERPICKUPCOMMAND_H

