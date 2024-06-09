#ifndef ENEMYSTUNNSTATE_H
#define ENEMYSTUNNSTATE_H

#include "EnemyState.h"

class EnemyStunState final : public EnemyState
{
public:

	explicit EnemyStunState(Enemy* const enemy, EnemyStateHandler* handler);
	virtual ~EnemyStunState() = default;

	virtual void Update() override;

private:

	static const float s_StunDuration;
	float m_CurrentStunTime;

	// animation

};

#endif // !ENEMYSTUNNSTATE_H