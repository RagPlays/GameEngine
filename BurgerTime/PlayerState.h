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

	virtual void SceneStart() override{};
	virtual void OnEnter() override{};
	virtual void OnExit() override{};
	virtual void FixedUpdate() override{};
	virtual void Update() override{};
	virtual void LateUpdate() override{};

protected:

	Player* const m_pPlayer;
	PlayerStateHandler* const m_pHandler;

};

#endif // !PLAYERSTATE_H