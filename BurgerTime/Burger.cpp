#include "Burger.h"
#include "BurgerPart.h"

Burger::Burger(MoE::GameObject* const owner)
	: Component{ owner }
{
}

void Burger::FixedUpdate()
{
}

void Burger::Update()
{
}

void Burger::Render() const
{
	/*for (const auto& burgerPart : m_BurgerParts)
	{
		burgerPart.Render();
	}*/
}