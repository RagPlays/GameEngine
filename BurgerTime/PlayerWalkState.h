#ifndef PLAYERWALKSTATE_H

#include <glm.hpp>
#include <memory>

#include "PlayerState.h"

namespace MoE
{
	class RenderComponent;
}
class Animation;

class PlayerWalkState final : public PlayerState
{
public:

	explicit PlayerWalkState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerWalkState();

	PlayerWalkState(const PlayerWalkState& other) = delete;
	PlayerWalkState(PlayerWalkState&& other) noexcept = delete;
	PlayerWalkState& operator=(const PlayerWalkState& other) = delete;
	PlayerWalkState& operator=(PlayerWalkState&& other) noexcept = delete;

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

private:

	void InitAnimations();
	void ChangeAnimation();
	void SetAnimation(Animation* animation, bool flipped = false);

private:

	// Components
	MoE::RenderComponent* m_pRenderComp;

	// Movement
	glm::ivec2 m_MovementSpeed;
	glm::ivec2 m_PreviousDir;
	glm::ivec2 m_HitBoxSize;

	// Animations
	Animation* m_pCurrentAnimation;

	std::unique_ptr<Animation> m_UpAnimation;
	std::unique_ptr<Animation> m_DownAnimation;
	std::unique_ptr<Animation> m_SidewayAnimation;

};

#endif // !PLAYERWALKSTATE_H
