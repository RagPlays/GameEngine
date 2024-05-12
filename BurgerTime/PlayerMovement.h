#ifndef PLAYERMOVEMENTCOMPONENT_H
#define PLAYERMOVEMENTCOMPONENT_H

#include "Component.h"

class PlayerMovement final : public Component
{
public:

	PlayerMovement(GameObject* const owner);
	~PlayerMovement() = default;

	virtual void GameStart() override;
	virtual void FixedUpdate() override;

	// Getters
	const glm::ivec2& GetHitBox() const;
	const glm::ivec2& GetMoveDir() const;
	const glm::vec2& GetPosition() const;
	void SetPosition(const glm::vec2& pos);

	// Movement
	void Move(const glm::ivec2& dir);
	void Stop(const glm::ivec2& dir);
	void SetPosition(const glm::ivec2& pos);

private:

	glm::ivec2 m_PlayerSpeed;
	glm::ivec2 m_MovementDir;
	glm::ivec2 m_HitBoxSize;

};

#endif // !PLAYERMOVEMENTCOMPONENT_H
