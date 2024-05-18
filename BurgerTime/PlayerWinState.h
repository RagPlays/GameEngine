#ifndef PLAYERWINSTATE_H
#define PLAYERWINSTATE_H

#include "PlayerState.h"

class PlayerWinState final : public PlayerState
{
public:

	explicit PlayerWinState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerWinState() = default;

	PlayerWinState(const PlayerWinState& other) = delete;
	PlayerWinState(PlayerWinState&& other) noexcept = delete;
	PlayerWinState& operator=(const PlayerWinState& other) = delete;
	PlayerWinState& operator=(PlayerWinState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

private:

};

#endif // !PLAYERWINSTATE_H
