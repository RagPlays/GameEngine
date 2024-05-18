#ifndef PLAYERATTACKSTATE_H
#define PLAYERATTACKSTATE_H

#include "PlayerState.h"

class PlayerAttackState final : public PlayerState
{
public:

	explicit PlayerAttackState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerAttackState() = default;

	PlayerAttackState(const PlayerAttackState& other) = delete;
	PlayerAttackState(PlayerAttackState&& other) noexcept = delete;
	PlayerAttackState& operator=(const PlayerAttackState& other) = delete;
	PlayerAttackState& operator=(PlayerAttackState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

private:

};

#endif // !PLAYERATTACKSTATE_H