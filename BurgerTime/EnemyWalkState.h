#ifndef ENEMYWALKSTATE_H
#define ENEMYWALKSTATE_H

#include <glm.hpp>

#include <memory>

#include "EnemyState.h"

namespace MoE
{
	class TextureRenderer;
}

class Player;
class Animation;
class LevelCollision;

class EnemyWalkState final : public EnemyState
{
public:

	explicit EnemyWalkState(Enemy* const enemy, EnemyStateHandler* handler);
	virtual ~EnemyWalkState();

	virtual void SceneStart() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;

	virtual void OnNotify(MoE::GameObject* gameObj, EventID eventID) override;

private:

	void InitAnimation();
	
	void ChangeAnimation();
	void SetAnimation(Animation* animation, bool flipped = false);

	void UpdateMovement();
	bool TryMove(const glm::ivec2& dir, LevelCollision* coll);

	void UpdateAnimation();

	Player* GetClosestPlayer() const;

private:

	// Physics
	glm::ivec2 m_MoveDir;
	const glm::ivec2 m_MovementSpeed;
	bool m_CanChangeDir;
	const float m_WaitUntilDirChange;
	float m_CurrentDirChangeWait;

	// Component
	MoE::TextureRenderer* m_pRenderComp;

	// Animations
	Animation* m_pCurrentAnimation;
	
	std::unique_ptr<Animation> m_UpAnimation;
	std::unique_ptr<Animation> m_DownAnimation;
	std::unique_ptr<Animation> m_SidewayAnimation;

};

#endif // !ENEMYWALKSTATE_H
