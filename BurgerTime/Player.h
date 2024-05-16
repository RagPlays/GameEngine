#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"
#include "Subject.h"

#include "PlayerStateHandler.h"

namespace MoE
{
	class RenderComponent;
}

class PlayerMovement;

class Player final : public MoE::Component, public MoE::Subject
{
public:

	explicit Player(MoE::GameObject* const owner);
	virtual ~Player();

	Player(const Player& other) = delete;
	Player(Player&& other) noexcept = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) noexcept = delete;
	
	// Overrides
	virtual void SceneStart() override;

	// Movement
	void Move(const glm::ivec2& dir);
	void Stop(const glm::ivec2& dir);


	// Player Info
	int GetPlayerIdx() const;

	// Components
	PlayerMovement* GetMovementComponent() const;
	MoE::RenderComponent* GetRenderComponent() const;

private:

	// Player Info
	static unsigned int s_PlayerCount;
	const unsigned int m_PlayerIdx;

	// Player States
	//PlayerStateHandler m_StateHandler;

	// Player Components
	PlayerMovement* m_pPlayerMovement;
	MoE::RenderComponent* m_pRenderComponent;

};

#endif // !PLAYERCOMPONENT_H