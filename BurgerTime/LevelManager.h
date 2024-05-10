#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

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

	Level* GetLevel() const;
	LevelRenderer* GetRenderer() const;
	LevelCollision* GetCollision() const;

private:

	friend class Singleton<LevelManager>;
	LevelManager() = default;

private:

	Level* m_pCurrentLevel;
	LevelRenderer* m_pCurrentLevelRenderer;
	LevelCollision* m_pCurrentLevelCollision;

};

#endif // !LEVELMANAGER_H
