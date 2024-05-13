#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <memory>

class Player;

class PlayerState
{
public:

	PlayerState() = default;
	virtual ~PlayerState() = default;

	PlayerState(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) noexcept = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState& operator=(PlayerState&& other) noexcept = delete;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Update(Player* const player) = 0;

public:

	static std::unique_ptr<PlayerState> m_IdleState;
	static std::unique_ptr<PlayerState> m_MoveUpState;
	static std::unique_ptr<PlayerState> m_MoveDownState;
	static std::unique_ptr<PlayerState> m_MoveLeftState;
	static std::unique_ptr<PlayerState> m_MoveRightState;

};

class PlayerIdleState final : public PlayerState
{
public:

	PlayerIdleState() = default;
	virtual ~PlayerIdleState() = default;

	PlayerIdleState(const PlayerIdleState& other) = delete;
	PlayerIdleState(PlayerIdleState&& other) noexcept = delete;
	PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(Player* const player) override;

private:

};

class PlayerMoveUpState final : public PlayerState
{
public:

	PlayerMoveUpState() = default;
	virtual ~PlayerMoveUpState() = default;

	PlayerMoveUpState(const PlayerMoveUpState& other) = delete;
	PlayerMoveUpState(PlayerMoveUpState&& other) noexcept = delete;
	PlayerMoveUpState& operator=(const PlayerMoveUpState& other) = delete;
	PlayerMoveUpState& operator=(PlayerMoveUpState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(Player* const player) override;

private:

};

class PlayerMoveDownState final : public PlayerState
{
public:

	PlayerMoveDownState() = default;
	virtual ~PlayerMoveDownState() = default;

	PlayerMoveDownState(const PlayerMoveDownState& other) = delete;
	PlayerMoveDownState(PlayerMoveDownState&& other) noexcept = delete;
	PlayerMoveDownState& operator=(const PlayerMoveDownState& other) = delete;
	PlayerMoveDownState& operator=(PlayerMoveDownState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(Player* const player) override;

private:

};

class PlayerMoveLeftState final : public PlayerState
{
public:

	PlayerMoveLeftState() = default;
	virtual ~PlayerMoveLeftState() = default;

	PlayerMoveLeftState(const PlayerMoveLeftState& other) = delete;
	PlayerMoveLeftState(PlayerMoveLeftState&& other) noexcept = delete;
	PlayerMoveLeftState& operator=(const PlayerMoveLeftState& other) = delete;
	PlayerMoveLeftState& operator=(PlayerMoveLeftState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(Player* const player) override;

private:

};

class PlayerMoveRightState final : public PlayerState
{
public:

	PlayerMoveRightState() = default;
	virtual ~PlayerMoveRightState() = default;

	PlayerMoveRightState(const PlayerMoveRightState& other) = delete;
	PlayerMoveRightState(PlayerMoveRightState&& other) noexcept = delete;
	PlayerMoveRightState& operator=(const PlayerMoveRightState& other) = delete;
	PlayerMoveRightState& operator=(PlayerMoveRightState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(Player* const player) override;

private:

};

#endif // !PLAYERSTATE_H
