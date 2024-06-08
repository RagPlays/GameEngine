#include "EnemyStateHandler.h"
#include "LevelManager.h"
#include "EnemyState.h"
#include "Enemy.h"

EnemyStateHandler::EnemyStateHandler(MoE::GameObject* const owner, Enemy* const enemy)
	: Component{ owner }
	, Observer{ &LevelManager::Get() }
	, m_pEnemy{ enemy }
	, m_pCurrentState{}
	, m_WalkState{}
	, m_StunnedState{}
	, m_DieState{}
{
	const EnemyType type{ m_pEnemy->GetType() };
	switch (type)
	{
	case EnemyType::hotdog:
		break;

	case EnemyType::egg:
		break;

	case EnemyType::pickle:
		break;
	}
}

void EnemyStateHandler::SceneStart()
{
	if (m_WalkState) m_WalkState->SceneStart();
	if (m_StunnedState) m_StunnedState->SceneStart();
	if (m_DieState) m_DieState->SceneStart();

	m_pCurrentState = m_WalkState.get();
	if (m_pCurrentState) m_pCurrentState->OnEnter();
}

void EnemyStateHandler::FixedUpdate()
{
	if (m_pCurrentState) m_pCurrentState->FixedUpdate();
}

void EnemyStateHandler::Update()
{
	if (m_pCurrentState) m_pCurrentState->Update();
}

void EnemyStateHandler::LateUpdate()
{
	if (m_pCurrentState) m_pCurrentState->LateUpdate();
}

void EnemyStateHandler::OnNotify(MoE::GameObject* gameObj, EventID eventID)
{
	if (m_pCurrentState) m_pCurrentState->OnNotify(gameObj, eventID);
}

void EnemyStateHandler::SetState(EnemyState* enemyState)
{
	if (!enemyState || m_pCurrentState == enemyState) return;
	if (m_pCurrentState)
	{
		m_pCurrentState->OnExit();
	}
	m_pCurrentState = enemyState;
	m_pCurrentState->OnEnter();
}

void EnemyStateHandler::SetWalkState()
{
	SetState(m_WalkState.get());
}

void EnemyStateHandler::SetStunnedState()
{
	SetState(m_StunnedState.get());
}

void EnemyStateHandler::SetDieState()
{
	SetState(m_DieState.get());
}