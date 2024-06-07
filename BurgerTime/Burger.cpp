#include "Burger.h"
#include "Structs.h"
#include "Collisions.h"
#include "TextureRenderer.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "BurgerPart.h"

#if defined DEBUG || defined _DEBUG
#include "Renderer.h"
#endif

Burger::Burger(MoE::GameObject* const owner, std::shared_ptr<MoE::Texture2D> texture, int burgerType)
	: MoE::Component{ owner }
	, m_Dimentions{}
	, m_BurgerParts{}
{
	LoadBurgerParts(burgerType, texture);
}

void Burger::CheckForCollision(const MoE::Rectf& hitbox)
{
	const MoE::Rectf burgerHitBox{ GetOwner()->GetWorldPosition(), static_cast<glm::vec2>(m_Dimentions) };
	if (MoE::Coll::OverLapping(hitbox, burgerHitBox))
	{
		for (auto& burgerPart : m_BurgerParts)
		{
			burgerPart->CheckForCollision(hitbox);
		}
	}
}

void Burger::LoadBurgerParts(int burgerType, std::shared_ptr<MoE::Texture2D> texture)
{
	const size_t nrOfBurgerParts{ 4 };
	m_BurgerParts.reserve(nrOfBurgerParts);

	const int gameScale{ GameManager::Get().GetGameScale() };

	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
	const int renderTileSize{ tileSize * gameScale };
	const int half{ tileSize / 2 };

	m_Dimentions = glm::ivec2{ renderTileSize * 2, renderTileSize / 2 };

	for (size_t burgerIdx{}; burgerIdx < nrOfBurgerParts; ++burgerIdx)
	{
		std::unique_ptr<MoE::GameObject> burgerPartObj{ std::make_unique<MoE::GameObject>() };
		MoE::GameObject* burgerPartObjPtr{ burgerPartObj.get() };

		const MoE::Recti srcRect{ half * static_cast<int>(burgerIdx), half * burgerType, half, half };
		auto burgerPartRenderC{ std::make_unique<MoE::TextureRenderer>(burgerPartObj.get(), texture) };
		burgerPartRenderC->SetSourceRect(srcRect);
		burgerPartRenderC->SetTextureDimensions(glm::ivec2{ m_Dimentions.x / nrOfBurgerParts,  m_Dimentions.y });

		auto burgerPart{ std::make_unique<BurgerPart>(burgerPartObj.get(), glm::ivec2{ renderTileSize / 2, renderTileSize / 2 }) };
		BurgerPart* burgerPartPtr{ burgerPart.get() };
		m_BurgerParts.emplace_back(burgerPartPtr);

		burgerPartObj->AddComponent(std::move(burgerPartRenderC));
		burgerPartObj->AddComponent(std::move(burgerPart));

		GetOwner()->AddChild(std::move(burgerPartObj));
		
		const glm::vec2 pos{ burgerIdx * renderTileSize / 2, 0.f };
		burgerPartObjPtr->SetLocalPosition(pos);
	}
}