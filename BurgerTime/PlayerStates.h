#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <memory>
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
	virtual void Update() = 0;

protected:

	void SetState(PlayerState* playerState);

protected:

	Player* const m_pPlayer;
	PlayerStateHandler* const m_pHandler;

};

class PlayerIdleState final : public PlayerState
{
public:

	explicit PlayerIdleState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerIdleState() = default;

	PlayerIdleState(const PlayerIdleState& other) = delete;
	PlayerIdleState(PlayerIdleState&& other) noexcept = delete;
	PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

};

class PlayerMoveUpState final : public PlayerState
{
public:

	explicit PlayerMoveUpState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerMoveUpState() = default;

	PlayerMoveUpState(const PlayerMoveUpState& other) = delete;
	PlayerMoveUpState(PlayerMoveUpState&& other) noexcept = delete;
	PlayerMoveUpState& operator=(const PlayerMoveUpState& other) = delete;
	PlayerMoveUpState& operator=(PlayerMoveUpState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

};

class PlayerMoveDownState final : public PlayerState
{
public:

	explicit PlayerMoveDownState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerMoveDownState() = default;

	PlayerMoveDownState(const PlayerMoveDownState& other) = delete;
	PlayerMoveDownState(PlayerMoveDownState&& other) noexcept = delete;
	PlayerMoveDownState& operator=(const PlayerMoveDownState& other) = delete;
	PlayerMoveDownState& operator=(PlayerMoveDownState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

};

class PlayerMoveLeftState final : public PlayerState
{
public:

	explicit PlayerMoveLeftState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerMoveLeftState() = default;

	PlayerMoveLeftState(const PlayerMoveLeftState& other) = delete;
	PlayerMoveLeftState(PlayerMoveLeftState&& other) noexcept = delete;
	PlayerMoveLeftState& operator=(const PlayerMoveLeftState& other) = delete;
	PlayerMoveLeftState& operator=(PlayerMoveLeftState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

};

class PlayerMoveRightState final : public PlayerState
{
public:

	explicit PlayerMoveRightState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerMoveRightState() = default;

	PlayerMoveRightState(const PlayerMoveRightState& other) = delete;
	PlayerMoveRightState(PlayerMoveRightState&& other) noexcept = delete;
	PlayerMoveRightState& operator=(const PlayerMoveRightState& other) = delete;
	PlayerMoveRightState& operator=(PlayerMoveRightState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

};

#endif // !PLAYERSTATE_H
