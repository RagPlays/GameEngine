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

class Burger final : public MoE::Component
{
public:

	explicit Burger(MoE::GameObject* const owner, std::shared_ptr<MoE::Texture2D> texture, int burgerType);
	virtual ~Burger() = default;

	Burger(const Burger& other) = delete;
	Burger(Burger&& other) noexcept = delete;
	Burger& operator=(const Burger& other) = delete;
	Burger& operator=(Burger&& other) noexcept = delete;

	void CheckForCollision(const MoE::Rectf& hitbox);

private:

	void LoadBurgerParts(int burgerType, std::shared_ptr<MoE::Texture2D> texture);

private:

	glm::ivec2 m_Dimentions;

	std::vector<BurgerPart*> m_BurgerParts;

};

#endif // !BURGER_H