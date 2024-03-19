#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"

class PlayerComponent final : public Component
{
public:
	PlayerComponent(GameObject* const owner, float moveSpeed = 200.f);
	~PlayerComponent() = default;

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) noexcept = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

	void Move(const glm::vec3& dir);

private:

	float m_PlayerSpeed;
};

#endif // !PLAYERCOMPONENT_H