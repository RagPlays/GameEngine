#ifndef ENEMYSTATEHANDLER_H
#define ENEMYSTATEHANDLER_H

#include <memory>

#include "Component.h"
#include "Observer.h"

namespace MoE
{
	class GameObject;
}

class Enemy;
class EnemyState;

using EventID = int;

class EnemyStateHandler final : public MoE::Component, public MoE::Observer
{
public:

	explicit EnemyStateHandler(MoE::GameObject* const owner, Enemy* const enemy);
	~EnemyStateHandler() = default;

	EnemyStateHandler(const EnemyStateHandler& other) = delete;
	EnemyStateHandler(EnemyStateHandler&& other) noexcept = delete;
	EnemyStateHandler& operator=(const EnemyStateHandler& other) = delete;
	EnemyStateHandler& operator=(EnemyStateHandler&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	virtual void OnNotify(MoE::GameObject* gameObj, EventID eventID) override;

	void SetState(EnemyState* enemyState);

	void SetWalkState();
	void SetStunnedState();
	void SetDieState();

private:

	Enemy* const m_pEnemy;

	EnemyState* m_pCurrentState;

	std::unique_ptr<EnemyState> m_WalkState;
	std::unique_ptr<EnemyState> m_StunnedState;
	std::unique_ptr<EnemyState> m_DieState;

};

#endif // !ENEMYSTATEHANDLER_H
