#include "Level.h"
#include "LevelManager.h"

using namespace MoE;

Level::Level(GameObject* const owner)
	: Component{ owner }
{
	LevelManager::Get().RegisterLevel(this);
}

Level::~Level()
{
	LevelManager::Get().UnRegisterLevel(this);
}