#ifndef ENEMYENDSTATE_H
#define ENEMYENDSTATE_H

#include "EnemyState.h"

class EnemyEndState final : public EnemyState
{
public:

	explicit EnemyEndState(Enemy* const enemy, EnemyStateHandler* handler);
	virtual ~EnemyEndState() = default;

	EnemyEndState(const EnemyEndState& other) = delete;
	EnemyEndState(EnemyEndState&& other) noexcept = delete;
	EnemyEndState& operator=(const EnemyEndState& other) = delete;
	EnemyEndState& operator=(EnemyEndState&& other) noexcept = delete;

private:

};

#endif // !ENEMYENDSTATE_H