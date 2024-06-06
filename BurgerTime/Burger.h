#ifndef BURGER_H
#define BURGER_H

#include <array>

#include "Component.h"
#include "BurgerPart.h"
#include "LevelBurgers.h"

namespace MoE
{
	class GameObject;
	class Texture2D;

	struct Recti;
}

class BurgerPart;

class Burger final : MoE::Component
{
public:

	explicit Burger(MoE::GameObject* const owner, std::shared_ptr<MoE::Texture2D> texture, BurgerPartType burgerType);
	virtual ~Burger() = default;

	Burger(const Burger& other) = delete;
	Burger(Burger&& other) noexcept = delete;
	Burger& operator=(const Burger& other) = delete;
	Burger& operator=(Burger&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void Render() const override;

	void CheckForCollision(const MoE::Rectf& hitbox);

private:

	BurgerPartType m_BurgerType;
	std::shared_ptr<MoE::Texture2D> m_Texture;
	MoE::Recti m_Hitbox;

	std::vector<BurgerPart> m_BurgerParts;

};

#endif // !BURGER_H