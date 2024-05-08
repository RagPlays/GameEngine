#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"
#include "Subject.h"

class PlayerComponent final : public Component, public Subject
{
public:

	explicit PlayerComponent(GameObject* const owner, float moveSpeed = 200.f);
	virtual ~PlayerComponent();

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) noexcept = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;
	
	// Overrides
	virtual void GameStart() override;
	virtual void FixedUpdate() override;

	// Player Info
	int GetPlayerIdx() const;

	// Movement
	void Move(const glm::ivec2& dir);
	void Stop(const glm::ivec2& dir);
	void FullStop();
	void SetPosition(const glm::ivec2& pos);

	// Health
	void Killed();

private:

	// Player Info
	static unsigned int s_PlayerCount;
	const unsigned int m_PlayerIdx;

	// Player Movement
	const float m_PlayerSpeed;
	glm::ivec2 m_MovementDir;
};

#endif // !PLAYERCOMPONENT_H