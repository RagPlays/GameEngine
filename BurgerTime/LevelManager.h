#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <glm.hpp>

#include "Singleton.h"

class Level;
class LevelCollision;
class LevelRenderer;

class LevelManager final : public Singleton<LevelManager>
{
public:

	~LevelManager() = default;

	void RegisterLevel(Level* level);
	void UnRegisterLevel(Level* level);

	uint8_t GetTileSize() const;

	Level* GetLevel() const;
	LevelRenderer* GetRenderer();
	LevelCollision* GetCollision();

private:

	friend class Singleton<LevelManager>;
	LevelManager();

private:

	const uint8_t m_TileSize;
	Level* m_pCurrentLevel;
	LevelRenderer* m_pCurrentLevelRenderer;
	LevelCollision* m_pCurrentLevelCollision;

};

#endif // !LEVELMANAGER_H