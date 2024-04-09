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
	virtual ~PlayerComponent() = default;

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) noexcept = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

	void Move(const glm::vec3& dir);
	void Killed();
	void PickupEvent(PickupItem item);

	int GetPlayerIdx() const;

private:

	static int s_playerCount;

	const int m_PlayerIdx;
	float m_PlayerSpeed;
};

#endif // !PLAYERCOMPONENT_H