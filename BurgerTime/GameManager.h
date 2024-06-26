#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <glm.hpp>

#include "Singleton.h"

class Engine;

class GameManager final : public MoE::Singleton<GameManager>
{
public:

	virtual ~GameManager() = default;

	int GetGameScale() const;
	const glm::ivec2& GetWindowSize() const;

private:

	friend MoE::Singleton<GameManager>;
	GameManager();

private:

	// Game Specs //
	const int m_GameScale;
	const glm::ivec2 m_DefaultWindowSize;
	const glm::ivec2 m_WindowSize;
	
};

#endif // !GAMEMANAGER_H
