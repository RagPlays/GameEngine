#include <algorithm>

#include "Burger.h"
#include "Structs.h"
#include "Collisions.h"
#include "TextureRenderer.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "BurgerPart.h"
#include "LevelCollision.h"
#include "Timer.h"
#include "BurgerHolder.h"
#include "LevelEnemies.h"

#if defined DEBUG || defined _DEBUG
#include "Renderer.h"
#endif

Burger::Burger(MoE::GameObject* const owner, std::shared_ptr<MoE::Texture2D> texture, int burgerType, BurgerHolder* holder)
	: MoE::Component{ owner }
	, m_FallSpeed{ 45.f * GameManager::Get().GetGameScale() }
	, m_IsFalling{}
	, m_InHolder{}
	, m_Dimentions
	{
		static_cast<int>(LevelManager::Get().GetTileSize()) * GameManager::Get().GetGameScale() * 2,
		static_cast<int>(LevelManager::Get().GetTileSize()) * GameManager::Get().GetGameScale() / 2
	}
	, m_pHolder{ holder }
	, m_BurgerParts{}
{
	LoadBurgerParts(burgerType, texture);
}

void Burger::FixedUpdate()
{
	if (!m_IsFalling) return;

	UpdateFallingMovement();
}

void Burger::LateUpdate()
{
	if (!m_IsFalling) return;
	if (LevelEnemies* enemies{ LevelManager::Get().GetEnemies() }; enemies)
	{
		const glm::vec2& pos{ GetOwner()->GetWorldPosition() };
		const MoE::Recti hitbox{ pos, static_cast<glm::vec2>(m_Dimentions) };
		enemies->CheckForCollision(hitbox);
	}
}

void Burger::CheckForCollision(const MoE::Recti& hitbox)
{
	if (m_InHolder || m_IsFalling || m_BurgerParts.empty()) return;

	const MoE::Recti burgerHitBox{ static_cast<glm::ivec2>(GetOwner()->GetWorldPosition()), m_Dimentions };
	if (MoE::Coll::OverLapping(hitbox, burgerHitBox))
	{
		if (std::any_of(m_BurgerParts.begin(), m_BurgerParts.end(),
			[&hitbox](const auto& burgerPart)
			{
				return burgerPart->CheckForCollision(hitbox);
			}
		)) CheckBurgerFalling();
	}
}

void Burger::ForceFalling()
{
	m_IsFalling = true;
	for (auto& burgerPart : m_BurgerParts)
	{
		burgerPart->UnPush();
	}
	const float pushDist{ BurgerPart::GetPushDistance() };
	GetOwner()->Translate(glm::vec2{ 0.f, pushDist });
}

bool Burger::GetInHolder() const
{
	return m_InHolder;
}

const glm::ivec2& Burger::GetDimentions() const
{
	return m_Dimentions;
}

MoE::Recti Burger::GetHitBox() const
{
	const glm::ivec2& pos{ static_cast<glm::ivec2>(GetOwner()->GetWorldPosition()) };
	return MoE::Recti{ pos, m_Dimentions };
}

void Burger::LoadBurgerParts(int burgerType, std::shared_ptr<MoE::Texture2D> texture)
{
	const size_t nrOfBurgerParts{ 4 };
	m_BurgerParts.reserve(nrOfBurgerParts);

	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
	const int half{ tileSize / 2 };

	const glm::ivec2 texDim{ m_Dimentions.x / static_cast<int>(nrOfBurgerParts),  m_Dimentions.y };

	for (size_t burgerIdx{}; burgerIdx < nrOfBurgerParts; ++burgerIdx)
	{
		std::unique_ptr<MoE::GameObject> burgerPartObj{ std::make_unique<MoE::GameObject>() };
		MoE::GameObject* burgerPartObjPtr{ burgerPartObj.get() };

		const MoE::Recti srcRect{ half * static_cast<int>(burgerIdx), half * burgerType, half, half };
		auto burgerPartRenderC{ std::make_unique<MoE::TextureRenderer>(burgerPartObj.get(), texture) };
		burgerPartRenderC->SetSourceRect(srcRect);
		burgerPartRenderC->SetTextureDimensions(texDim);

		auto burgerPart{ std::make_unique<BurgerPart>(burgerPartObj.get(), glm::ivec2{ m_Dimentions.y, m_Dimentions.y }) };
		BurgerPart* burgerPartPtr{ burgerPart.get() };
		m_BurgerParts.emplace_back(burgerPartPtr);

		burgerPartObj->AddComponent(std::move(burgerPartRenderC));
		burgerPartObj->AddComponent(std::move(burgerPart));

		GetOwner()->AddChild(std::move(burgerPartObj));
		
		const glm::vec2 pos{ burgerIdx * m_Dimentions.y, 0.f };
		burgerPartObjPtr->SetLocalPosition(pos);
	}
}

void Burger::CheckBurgerFalling()
{
	if (std::all_of(m_BurgerParts.begin(), m_BurgerParts.end(),
		[](const auto& burgerPart)
		{
			return burgerPart->GetIsPushed();
		}
	)) ForceFalling();
}

void Burger::UpdateFallingMovement()
{
	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		MoE::GameObject* const owner{ GetOwner() };
		const int holdHeight{ m_pHolder->GetCurrentHoldHeight() };

		if (int collFallPos{ coll->GetNextBurgerFallPos(static_cast<glm::ivec2>(owner->GetWorldPosition())) })
		{
			const int fallPos{ collFallPos < holdHeight ? collFallPos : holdHeight };
			const float fallDist{ m_FallSpeed * MoE::Timer::Get().GetFixedElapsedSec() };

			owner->Translate(glm::vec2{ 0.f, fallDist });

			if (owner->GetWorldPosition().y >= fallPos)
			{
				const glm::vec2& pos{ owner->GetWorldPosition() };
				owner->SetWorldPosition(glm::vec2{ pos.x, static_cast<float>(fallPos) });
				m_IsFalling = false;
				if (holdHeight == fallPos)
				{
					m_InHolder = true;
					m_pHolder->CheckInHolder();
					return;
				}
				m_pHolder->CheckOverLapping(this);
			}
		}
	}
}