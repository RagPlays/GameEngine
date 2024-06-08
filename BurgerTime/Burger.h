#ifndef BURGER_H
#define BURGER_H

#include <vector>
#include <memory>

#include <glm.hpp>

#include "Component.h"
#include "Structs.h"

namespace MoE
{
	class GameObject;
	class Texture2D;

	struct Recti;
}

class BurgerPart;
class BurgerHolder;

class Burger final : public MoE::Component
{
public:

	explicit Burger(MoE::GameObject* const owner, std::shared_ptr<MoE::Texture2D> texture, int burgerType, BurgerHolder* holder);
	virtual ~Burger() = default;

	Burger(const Burger& other) = delete;
	Burger(Burger&& other) noexcept = delete;
	Burger& operator=(const Burger& other) = delete;
	Burger& operator=(Burger&& other) noexcept = delete;

	virtual void FixedUpdate() override;

	void CheckForCollision(const MoE::Recti& hitbox);

	void ForceFalling();

	bool GetInHolder() const;
	const glm::ivec2& GetDimentions() const;
	MoE::Recti GetHitBox() const;

private:

	void LoadBurgerParts(int burgerType, std::shared_ptr<MoE::Texture2D> texture);
	void CheckBurgerFalling();

private:

	float m_FallSpeed;
	bool m_InHolder;
	bool m_IsFalling;
	glm::ivec2 m_Dimentions;

	BurgerHolder* m_pHolder;
	std::vector<BurgerPart*> m_BurgerParts;

};

#endif // !BURGER_H