#include <iostream>
#include <limits>

#include "BurgerHolder.h"
#include "Burger.h"
#include "Collisions.h"
#include "LevelManager.h"
#include "LevelBurgers.h"

#if defined DEBUG || defined _DEBUG
#include "Renderer.h"
#include "GameObject.h"
#endif

BurgerHolder::BurgerHolder(int nrOfBurgers, int holdHeight)
	: m_Burgers{}
	, m_FullSizeNr{ nrOfBurgers }
	, m_CurrentSizeNr{}
	, m_BurgerHoldHeight{ holdHeight }
{
	m_Burgers.reserve(nrOfBurgers);
}

#if defined DEBUG || defined _DEBUG
void BurgerHolder::Render() const
{
	if (m_Burgers.empty()) return;

	const glm::ivec2& dim{ m_Burgers[0]->GetDimentions() };
	const int xPos{ static_cast<int>(m_Burgers[0]->GetOwner()->GetWorldPosition().x) };

	const MoE::Linei drawLine
	{
		glm::ivec2{ xPos, GetCurrentHoldHeight() },
		glm::ivec2{ xPos + dim.x, GetCurrentHoldHeight() }
	};

	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.SetCurrentDrawColor(MoE::Color{ 0, 255, 0 });
	renderer.RenderLine(drawLine);
}
#endif

void BurgerHolder::AddBurger(Burger* burger)
{
	if (m_Burgers.size() < m_FullSizeNr) m_Burgers.emplace_back(burger);
	else std::cerr << "ERROR::BURGERHOLDER::CANT_ADD_MORE_THEN_LIMIT\n";
}

void BurgerHolder::CheckForCollision(const MoE::Recti& hitbox)
{
	for (auto& burger : m_Burgers)
	{
		burger->CheckForCollision(hitbox);
	}
}

void BurgerHolder::CheckInHolder()
{
	m_CurrentSizeNr = 0;
	for (const auto& burger : m_Burgers)
	{
		if (burger->GetInHolder()) ++m_CurrentSizeNr;
	}
	if (IsHolderCompleted()) LevelManager::Get().GetBurgers()->CheckLevelCompleted();
}

void BurgerHolder::CheckOverLapping(Burger* checkBurger)
{
	for (auto& burger : m_Burgers)
	{
		if (burger == checkBurger) continue;
		if (MoE::Coll::OverLapping(burger->GetHitBox(), checkBurger->GetHitBox())) burger->ForceFalling();
	}
}

int BurgerHolder::GetCurrentHoldHeight() const
{
	if (m_Burgers.empty()) return std::numeric_limits<int>::max();
	return (m_BurgerHoldHeight - (m_CurrentSizeNr * m_Burgers[0]->GetDimentions().y));
}

bool BurgerHolder::IsHolderCompleted() const
{
	return m_CurrentSizeNr >= m_FullSizeNr;
}