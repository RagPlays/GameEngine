#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"
#include "Subject.h"

class Player final : public Component, public Subject
{
public:

	explicit Player(GameObject* const owner);
	virtual ~Player();

	Player(const Player& other) = delete;
	Player(Player&& other) noexcept = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) noexcept = delete;
	
	// Overrides
	virtual void GameStart() override;

	// Player Info
	int GetPlayerIdx() const;

	// Health
	void Killed();

private:

	// Player Info
	static unsigned int s_PlayerCount;
	const unsigned int m_PlayerIdx;

};

#endif // !PLAYERCOMPONENT_H