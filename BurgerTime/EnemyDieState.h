#ifndef ENEMYDIESTATE_H
#define ENEMYDIESTATE_H

#include <memory>

#include "EnemyState.h"
#include "Enemy.h"

namespace MoE
{
	class TextureRenderer;
}

class Animation;

class EnemyDieState final : public EnemyState
{
public:

	explicit EnemyDieState(Enemy* const enemy, EnemyStateHandler* const handler);
	virtual ~EnemyDieState();

	EnemyDieState(const EnemyDieState& other) = delete;
	EnemyDieState(EnemyDieState&& other) noexcept = delete;
	EnemyDieState& operator=(const EnemyDieState& other) = delete;
	EnemyDieState& operator=(EnemyDieState&& other) noexcept = delete;


	virtual void SceneStart() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

	void InitAnimation(MoE::TextureRenderer* renderComp);

private:

	std::unique_ptr<Animation> m_DieAnimation;

};

#endif // !ENEMYDIESTATE_H