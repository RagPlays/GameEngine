#ifndef PLAYERMOVEMENTCOMPONENT_H
#define PLAYERMOVEMENTCOMPONENT_H

#include "Component.h"

class PlayerMovementComponent final : public Component
{
public:

	PlayerMovementComponent(GameObject* const owner, float movementSpeed);
	~PlayerMovementComponent() = default;

	virtual void FixedUpdate() override;

	// Movement
	void Move(const glm::ivec2& dir);
	void Stop(const glm::ivec2& dir);
	void SetPosition(const glm::ivec2& pos);

private:

	float m_PlayerSpeed;
	glm::ivec2 m_MovementDir;
};

#endif // !PLAYERMOVEMENTCOMPONENT_H
