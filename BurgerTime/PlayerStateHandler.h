#ifndef PLAYERSTAEHANDLER_H
#define PLAYERSTAEHANDLER_H

#include <memory>

#include "Component.h"
#include "Observer.h"

using EventID = int;

class Player;
class PlayerState;

class PlayerStateHandler final : public MoE::Component, public MoE::Observer
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

	virtual void OnNotify(MoE::GameObject* gameObj, EventID eventID) override;

	void Notify(EventID eventID);

	void SetState(PlayerState* playerState);

	void SetWalkState();
	void SetAttackState();
	void SetWinState();
	void SetDieState();

private:

	Player* const m_pPlayer;

	PlayerState* m_pCurrentState;

	std::unique_ptr<PlayerState> m_WalkState;
	std::unique_ptr<PlayerState> m_AttackState;
	std::unique_ptr<PlayerState> m_WinState;
	std::unique_ptr<PlayerState> m_DieState;

};

#endif // !PLAYERSTAEHANDLER_H
