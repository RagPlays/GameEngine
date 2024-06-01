#ifndef PLAYERDIESTATE_H
#define PLAYERDIESTATE_H

#include <memory>

#include "PlayerState.h"

namespace MoE
{
	class TextureRenderer;
}
class Animation;

class PlayerDieState final : public PlayerState
{
public:

	explicit PlayerDieState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerDieState();

	PlayerDieState(const PlayerDieState& other) = delete;
	PlayerDieState(PlayerDieState&& other) noexcept = delete;
	PlayerDieState& operator=(const PlayerDieState& other) = delete;
	PlayerDieState& operator=(PlayerDieState&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

	void InitAnimations(MoE::TextureRenderer* renderComp);

	void SetAnimation(Animation* animation);

	void UpdateAnimations();
	void UpdateStateChange();

private:

	// Animations
	Animation* m_pCurrentAnimation;

	std::unique_ptr<Animation> m_CaughtAnimation;
	std::unique_ptr<Animation> m_FallAnimation;
	std::unique_ptr<Animation> m_DownAnimation;

};

#endif // !PLAYERDIESTATE_H
