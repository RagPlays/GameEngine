#ifndef PLAYERSTATSCOMPONENT_H
#define PLAYERSTATSCOMPONENT_H

#include "Component.h"
#include "Observer.h"

class Player;
class GameObject;

class PlayerStats final : public Component, public Observer
{
public:

	explicit PlayerStats(GameObject* const owner);
	virtual ~PlayerStats() = default;

	PlayerStats(const PlayerStats& other) = delete;
	PlayerStats(PlayerStats&& other) noexcept = delete;
	PlayerStats& operator=(const PlayerStats& other) = delete;
	PlayerStats& operator=(PlayerStats&& other) noexcept = delete;

	void Update() override;

	void OnNotify(GameObject* gameObj, GameEvent gameEvent) override;

private:

	bool m_NeedsUpdate;
	int m_PlayerIdx;
	int m_Lives;
	int m_Score;

};

#endif // !PLAYERSTATE