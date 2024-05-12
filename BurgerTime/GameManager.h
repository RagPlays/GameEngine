#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <glm.hpp>

#include "Singleton.h"

class Engine;

class GameManager final : public Singleton<GameManager>
{
public:

	virtual ~GameManager() = default;

	const int GetGameScale() const;
	const glm::ivec2& GetWindowSize() const;

private:

	friend Singleton<GameManager>;
	GameManager();

private:

	// Game Specs //

	const int m_GameScale;
	const glm::ivec2 m_DefaultWindowSize;
	const glm::ivec2 m_WindowSize;
	
	// int score
};

#endif // !GAMEMANAGER_H
