#ifndef BURGERPART_H
#define BURGERPART_H

#include <memory>

#include "Component.h"

namespace MoE
{
	struct Rectf;
}

class BurgerPart final : public MoE::Component
{
public:

	explicit BurgerPart(MoE::GameObject* const owner, const glm::ivec2& dimentions);
	virtual ~BurgerPart() = default;

#if defined DEBUG || defined _DEBUG
	virtual void Render() const override;
#endif

	bool GetIsPushed() const;

	void CheckForCollision(const MoE::Rectf& hitbox);

private:

	bool m_Pushed;
	float m_PushDistance;
	const glm::ivec2 m_Dimentions;

};

#endif // !BURGERPART_H