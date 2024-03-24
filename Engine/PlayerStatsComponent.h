#ifndef PLAYERSTATSCOMPONENT_H
#define PLAYERSTATSCOMPONENT_H

#include "Component.h"
#include "Observer.h"

class PlayerComponent;
class GameObject;

class PlayerStatsComponent final : public Component, public Observer
{
public:

	explicit PlayerStatsComponent(GameObject* const owner, PlayerComponent* const observedPlayer);
	virtual ~PlayerStatsComponent() = default;

	PlayerStatsComponent(const PlayerStatsComponent& other) = delete;
	PlayerStatsComponent(PlayerStatsComponent&& other) noexcept = delete;
	PlayerStatsComponent& operator=(const PlayerStatsComponent& other) = delete;
	PlayerStatsComponent& operator=(PlayerStatsComponent&& other) noexcept = delete;

	virtual void Update() override;

	virtual void OnNotify(GameObject* gameObj, GameEvent gameEvent) override;

private:

	bool m_NeedsUpdate;
	PlayerComponent* const m_ObservedPlayer;
};

#endif // !PLAYERSTATE