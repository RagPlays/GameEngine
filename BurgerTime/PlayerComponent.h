#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"
#include "Subject.h"

enum class PickupItem
{
	smallItem,
	bigItem
};

class PlayerComponent final : public Component, public Subject
{
public:

	explicit PlayerComponent(GameObject* const owner, float moveSpeed = 200.f);
	virtual ~PlayerComponent();

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) noexcept = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

	virtual void GameStart() override;

	virtual void FixedUpdate() override;

	void Move(const glm::ivec2& dir);
	void Stop(const glm::ivec2& stopDir);
	void Killed();
	void PickupEvent(PickupItem item);

	int GetPlayerIdx() const;

private:

	glm::ivec2 m_MovementDir;

	static unsigned int s_PlayerCount;

	const unsigned int m_PlayerIdx;
	float m_PlayerSpeed;
};

#endif // !PLAYERCOMPONENT_H