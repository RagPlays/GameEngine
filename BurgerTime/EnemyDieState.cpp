#include "EnemyDieState.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Animation.h"
#include "EnemyStateHandler.h"
#include "Enemy.h"

using namespace MoE;

EnemyDieState::EnemyDieState(Enemy* const enemy, EnemyStateHandler* const handler)
	: EnemyState{ enemy, handler }
{
}

EnemyDieState::~EnemyDieState() = default;

void EnemyDieState::SceneStart()
{
	if (TextureRenderer* renderComp{ m_pEnemy->GetOwner()->GetComponent<TextureRenderer>() }; renderComp)
	{
		InitAnimation(renderComp);
	}
}

void EnemyDieState::OnEnter()
{
	m_DieAnimation->Play();
}

void EnemyDieState::OnExit()
{
	m_DieAnimation->Stop();
}

void EnemyDieState::Update()
{
	if (m_DieAnimation)
	{
		if (m_DieAnimation->Update())
		{
			m_pEnemy->Respawn();
		}
	}
}

void EnemyDieState::InitAnimation(TextureRenderer* renderComp)
{
	const int enemyType{ static_cast<int>(m_pEnemy->GetType()) };
	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
	const int typeOffset{ tileSize * 2 * enemyType };

	m_DieAnimation = std::make_unique<Animation>(renderComp, static_cast<uint8_t>(4), static_cast<uint8_t>(2));
	const MoE::Recti die1Rect{ 0 * tileSize, 1 * tileSize + typeOffset, tileSize, tileSize };
	const MoE::Recti die2Rect{ 1 * tileSize, 1 * tileSize + typeOffset, tileSize, tileSize };
	const MoE::Recti die3Rect{ 2 * tileSize, 1 * tileSize + typeOffset, tileSize, tileSize };
	const MoE::Recti die4Rect{ 3 * tileSize, 1 * tileSize + typeOffset, tileSize, tileSize };
	m_DieAnimation->AddFrame(die1Rect);
	m_DieAnimation->AddFrame(die2Rect);
	m_DieAnimation->AddFrame(die3Rect);
	m_DieAnimation->AddFrame(die4Rect);
}