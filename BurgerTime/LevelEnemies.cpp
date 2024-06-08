#include "LevelEnemies.h"
#include "Enemy.h"
#include "EnemyState.h"
#include "EnemyStateHandler.h"

LevelEnemies::LevelEnemies(MoE::GameObject* const owner, const std::string& loadPath, std::shared_ptr<MoE::Texture2D> texture)
	: Component{ owner }
{
	LoadEnemies(loadPath, texture);
}

void LevelEnemies::CheckForCollision(const MoE::Recti&)
{
}

void LevelEnemies::LoadEnemies(const std::string&, std::shared_ptr<MoE::Texture2D>)
{
}