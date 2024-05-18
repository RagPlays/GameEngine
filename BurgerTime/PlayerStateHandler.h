#ifndef PLAYERSTAEHANDLER_H
#define PLAYERSTAEHANDLER_H

#include <memory>

#include "Component.h"

class PlayerWalkState;
class PlayerAttackState;
class PlayerWinState;
class PlayerDieState;

class Player;
class PlayerState;

class PlayerStateHandler final : public MoE::Component
{
public:

	explicit PlayerStateHandler(MoE::GameObject* const owner, Player* const player);
	virtual ~PlayerStateHandler();

	PlayerStateHandler(const PlayerStateHandler& other) = delete;
	PlayerStateHandler(PlayerStateHandler&& other) noexcept = delete;
	PlayerStateHandler& operator=(const PlayerStateHandler& other) = delete;
	PlayerStateHandler& operator=(PlayerStateHandler&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	void SetState(PlayerState* playerState);

	void SetWalkState();
	void SetAttackState();
	void SetWinState();
	void SetDieState();

private:

	PlayerState* m_pCurrentState;

	std::unique_ptr<PlayerWalkState> m_WalkState;
	std::unique_ptr<PlayerAttackState> m_AttackState;
	std::unique_ptr<PlayerWinState> m_WinState;
	std::unique_ptr<PlayerDieState> m_DieState;

};

#endif // !PLAYERSTAEHANDLER_H
