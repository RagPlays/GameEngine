#ifndef PLAYERHEALTHSTATS_H
#define PLAYERHEALTHSTATS_H

#include <vector>

#include "Component.h"
#include "Observer.h"

using EventID = int;

namespace MoE
{
	class GameObject;
}

class Player;

class PlayerHealthStats final : public MoE::Component, public MoE::Observer
{
public:

	explicit PlayerHealthStats(MoE::GameObject* const owner, Player* const playerToObserve, uint8_t playerLives);
	~PlayerHealthStats() = default;

	PlayerHealthStats(const PlayerHealthStats& other) = delete;
	PlayerHealthStats(PlayerHealthStats&& other) noexcept = delete;
	PlayerHealthStats& operator=(const PlayerHealthStats& other) = delete;
	PlayerHealthStats& operator=(PlayerHealthStats&& other) noexcept = delete;

	virtual void OnNotify(MoE::GameObject* gameObj, EventID eventID) override;

private:

	uint8_t m_RemainingLives;

};

#endif // !PLAYERHEALTHSTATS_H
