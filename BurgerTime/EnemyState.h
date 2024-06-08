#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include "State.h"

namespace MoE
{
	class GameObject;
}

class Enemy;
class EnemyStateHandler;

using EventID = int;

class EnemyState : MoE::State
{
public:

	explicit EnemyState(Enemy* const enemy, EnemyStateHandler* const handler)
		: State{}
		, m_pEnemy{ enemy }
		, m_pHandler{ handler }
	{
	}
	virtual ~EnemyState() = default;

	EnemyState(const EnemyState& other) = delete;
	EnemyState(EnemyState&& other) noexcept = delete;
	EnemyState& operator=(const EnemyState& other) = delete;
	EnemyState& operator=(EnemyState&& other) noexcept = delete;

	virtual void SceneStart() override {};
	virtual void OnEnter() override {};
	virtual void OnExit() override {};
	virtual void FixedUpdate() override {};
	virtual void Update() override {};
	virtual void LateUpdate() override {};
	virtual void OnNotify(MoE::GameObject*, EventID) {};

protected:

	Enemy* const m_pEnemy;
	EnemyStateHandler* const m_pHandler;

};

#endif // !ENEMYSTATE_H
