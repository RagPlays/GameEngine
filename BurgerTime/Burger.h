#ifndef BURGER_H
#define BURGER_H

#include "Component.h"

namespace MoE
{
	class GameObject;
}

class Burger final : MoE::Component
{
public:

	explicit Burger(MoE::GameObject* const owner);
	virtual ~Burger() = default;

	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

	Burger(const Burger& other) = delete;
	Burger(Burger&& other) noexcept = delete;
	Burger& operator=(const Burger& other) = delete;
	Burger& operator=(Burger&& other) noexcept = delete;

private:

	// 4 burgerPieces Rects

	// has a rect on itself 

};

#endif // !BURGER_H