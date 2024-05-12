#include "Level.h"
#include "LevelManager.h"

Level::Level(GameObject* const owner)
	: Component{ owner }
{
	LevelManager::Get().RegisterLevel(this);
}

Level::~Level()
{
	LevelManager::Get().UnRegisterLevel(this);
}