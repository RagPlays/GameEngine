#include "Enemy.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "GameObject.h"

Enemy::Enemy(MoE::GameObject* const owner, EnemyType type)
	: Component{ owner }
	, m_Hitbox{}
	, m_Type{ type }
{	
}

void Enemy::SceneStart()
{
	const int gameScale{ GameManager::Get().GetGameScale() };
	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
	const int renderTileSize{ tileSize * gameScale };
	const glm::ivec2& pos{ static_cast<glm::ivec2>(GetOwner()->GetWorldPosition()) };

	m_Hitbox = MoE::Recti{ pos, glm::ivec2{ renderTileSize, renderTileSize } };
}

void Enemy::FixedUpdate()
{
}

EnemyType Enemy::GetType() const
{
	return m_Type;
}