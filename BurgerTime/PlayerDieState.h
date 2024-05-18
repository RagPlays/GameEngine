#ifndef PLAYERDIESTATE_H
#define PLAYERDIESTATE_H

#include "PlayerState.h"

class PlayerDieState final : public PlayerState
{
public:

	explicit PlayerDieState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerDieState() = default;

	PlayerDieState(const PlayerDieState& other) = delete;
	PlayerDieState(PlayerDieState&& other) noexcept = delete;
	PlayerDieState& operator=(const PlayerDieState& other) = delete;
	PlayerDieState& operator=(PlayerDieState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

private:
};

#endif // !PLAYERDIESTATE_H
