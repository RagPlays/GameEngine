#ifndef ENEMYDIESTATE_H
#define ENEMYDIESTATE_H

#include "EnemyState.h"
#include "Enemy.h"

class EnemyDieState final : public EnemyState
{
public:

	explicit EnemyDieState(Enemy* const enemy, EnemyStateHandler* const handler);
	virtual ~EnemyDieState() = default;

private:

	EnemyType m_EnemyType;

};

#endif // !ENEMYDIESTATE_H