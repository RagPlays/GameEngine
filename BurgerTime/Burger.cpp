#include "Burger.h"
#include "Structs.h"
#include "Collisions.h"
#include "LevelManager.h"

Burger::Burger(MoE::GameObject* const owner, std::shared_ptr<MoE::Texture2D> texture, BurgerPartType burgerType)
	: Component{ owner }
	, m_BurgerType{ burgerType }
	, m_Texture{ texture }
	, m_Hitbox{}
	, m_BurgerParts{}
{
	m_BurgerParts.reserve(4);
}

void Burger::SceneStart()
{
	//const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };

	//BurgerPart part1{}

	//m_BurgerParts.emplace_back()
}

void Burger::Render() const
{
	for (const auto& burgerPart : m_BurgerParts)
	{
		burgerPart.Render();
	}

#if defined DEBUG || defined _DEBUG
	


#endif

}

void Burger::CheckForCollision(const MoE::Rectf& hitbox)
{
	if (MoE::Coll::OverLapping(hitbox, static_cast<MoE::Rectf>(m_Hitbox)))
	{
		for (auto& burgerPart : m_BurgerParts)
		{
			burgerPart.CheckForCollision(hitbox);
		}
	}
}