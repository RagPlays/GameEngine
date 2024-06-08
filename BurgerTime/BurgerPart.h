#ifndef BURGERPART_H
#define BURGERPART_H

#include <memory>

#include "Component.h"

namespace MoE
{
	struct Rectf;
	struct Recti;
}

class BurgerPart final : public MoE::Component
{
public:

	explicit BurgerPart(MoE::GameObject* const owner, const glm::ivec2& dimentions);
	virtual ~BurgerPart() = default;

#if defined DEBUG || defined _DEBUG
	virtual void Render() const override;
#endif

	static float GetPushDistance();
	bool GetIsPushed() const;
	void UnPush();

	bool CheckForCollision(const MoE::Recti& hitbox);

private:

	static float s_PushDistance;

	bool m_Pushed;
	const glm::ivec2 m_Dimentions;

};

#endif // !BURGERPART_H