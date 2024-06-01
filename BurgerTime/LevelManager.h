#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <glm.hpp>

#include "Singleton.h"

class Level;
class LevelCollision;
class LevelRenderer;

class LevelManager final : public MoE::Singleton<LevelManager>
{
public:

	virtual ~LevelManager() = default;

	void RegisterLevel(Level* level);
	void UnRegisterLevel(Level* level);

	void NextLevel();

	uint8_t GetTileSize() const;

	Level* GetLevel() const;
	LevelRenderer* GetRenderer();
	LevelCollision* GetCollision();

private:

	friend class MoE::Singleton<LevelManager>;
	LevelManager();

private:

	int m_CurrentLevel;
	uint8_t m_NrLevelsCount;
	const uint8_t m_TileSize;
	Level* m_pCurrentLevel;
	LevelRenderer* m_pCurrentLevelRenderer;
	LevelCollision* m_pCurrentLevelCollision;

};

#endif // !LEVELMANAGER_H
