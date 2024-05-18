#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <State.h>

class Player;
class PlayerStateHandler;

class PlayerState : public MoE::State
{
public:

	explicit PlayerState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerState() = default;

	PlayerState(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) noexcept = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState& operator=(PlayerState&& other) noexcept = delete;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

protected:

	Player* const m_pPlayer;
	PlayerStateHandler* const m_pHandler;

};

#endif // !PLAYERSTATE_H