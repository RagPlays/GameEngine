#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <glm.hpp>

#include "Singleton.h"
#include "Subject.h"

using EventID = int;

class Player;

class Level;
class LevelCollision;
class LevelRenderer;
class LevelBurgers;
class LevelEnemies;

enum class GameMode
{
	singlePlayer,
	multiplayer,
	versus
};

class LevelManager final : public MoE::Singleton<LevelManager>, public MoE::Subject
{
public:

	virtual ~LevelManager() = default;

	void RegisterLevel(Level* const level);
	void UnRegisterLevel(Level* const level);

	void RegisterPlayer(Player* const player);
	void UnRegisterPlayer(Player* const player);

	void SetGameMode(GameMode gameMode);
	GameMode GetGameMode() const;

	void GoStartMenu();
	void StartGame();
	void GoInfoMenu();
	void NextLevel();
	void GameOver();

	uint8_t GetTileSize() const;

	const std::vector<Player*>& GetPlayers();

	Level* GetLevel() const;
	LevelRenderer* GetRenderer();
	LevelCollision* GetCollision();
	LevelBurgers* GetBurgers();
	LevelEnemies* GetEnemies();

private:

	friend class MoE::Singleton<LevelManager>;
	LevelManager();

private:

	GameMode m_GameMode;

	int m_CurrentLevel;
	uint8_t m_NrLevelsCount;
	const uint8_t m_TileSize;

	std::vector<Player*> m_pCurrentPlayers;

	Level* m_pCurrentLevel;
	LevelRenderer* m_pCurrentLevelRenderer;
	LevelCollision* m_pCurrentLevelCollision;
	LevelBurgers* m_pCurrentLevelBurgers;
	LevelEnemies* m_pCurrentLevelEnemies;

};

#endif // !LEVELMANAGER_H
