#ifndef PLAYERATTACKSTATE_H
#define PLAYERATTACKSTATE_H

#include <memory>

#include "PlayerState.h"

namespace MoE
{
	class TextureRenderer;
}

class Animation;

class PlayerAttackState final : public PlayerState
{
public:

	explicit PlayerAttackState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerAttackState();

	PlayerAttackState(const PlayerAttackState& other) = delete;
	PlayerAttackState(PlayerAttackState&& other) noexcept = delete;
	PlayerAttackState& operator=(const PlayerAttackState& other) = delete;
	PlayerAttackState& operator=(PlayerAttackState&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	virtual void OnNotify(MoE::GameObject* gameObj, EventID eventID) override;

private:

	void InitAnimations();

	void SetCorrectAnimation();
	void SetAnimation(Animation* animation, bool flipped = false);

	void UpdateAnimation();

private:

	// RenderComponent
	MoE::TextureRenderer* m_pRenderComp;

	// animations
	Animation* m_pCurrentAnimation;

	// up
	std::unique_ptr<Animation> m_UpAnimation;
	// down
	std::unique_ptr<Animation> m_DownAnimation;
	// sideway
	std::unique_ptr<Animation> m_SideAnimation;

};

#endif // !PLAYERATTACKSTATE_H