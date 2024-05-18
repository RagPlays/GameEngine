#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "Component.h"
#include "Subject.h"

#include "PlayerStateHandler.h"

namespace MoE
{
	class TextureRenderer;
}

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
	const glm::ivec2& GetMoveDir() const;

	// Player Info
	int GetPlayerIdx() const;

	// Components
	MoE::TextureRenderer* GetRenderComponent() const;

private:

	// Player Info
	static unsigned int s_PlayerCount;
	const unsigned int m_PlayerIdx;

	// Movement
	glm::ivec2 m_MovementDir;

	// Player Components
	MoE::TextureRenderer* m_pRenderComponent;

};

#endif // !PLAYERCOMPONENT_H