#include "EnemyStunState.h"
#include "Timer.h"

const float EnemyStunState::s_StunDuration{ 3.f };

EnemyStunState::EnemyStunState(Enemy* const enemy, EnemyStateHandler* handler)
	: EnemyState{ enemy, handler }
{
}

void EnemyStunState::Update()
{
	//m_CurrentStunTime += 
}