#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"
#include "Subject.h"

class PlayerComponent final : public Component, public Subject
{
public:

	explicit PlayerComponent(GameObject* const owner, float moveSpeed = 200.f);
	virtual ~PlayerComponent() = default;

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) noexcept = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

	void Move(const glm::vec3& dir);
	void Killed();
	void AddScore(int score);

	int GetPlayerIdx() const;
	int GetScore() const;
	int GetLives() const;

private:

	static int s_playerCount;

	const int m_PlayerIdx;
	int m_Score;
	int m_CurrentLives;
	float m_PlayerSpeed;
};

#endif // !PLAYERCOMPONENT_H