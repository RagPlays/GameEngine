#include <iostream>
#include <fstream>
#include <algorithm>

#include "LevelBurgers.h"
#include "Burger.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "BurgerHolder.h"
#include "EventIDs.h"

LevelBurgers::LevelBurgers(MoE::GameObject* const owner, const std::string& burgerLoadPath, std::shared_ptr<MoE::Texture2D> texture)
	: MoE::Component{ owner }
	, m_BurgerHolders{}
{
	LoadBurgers(burgerLoadPath, texture);
}

LevelBurgers::~LevelBurgers() = default;

#if defined DEBUG || defined _DEBUG
void LevelBurgers::Render() const
{
	for (auto& holders : m_BurgerHolders)
	{
		holders->Render();
	}
}
#endif

void LevelBurgers::CheckForCollision(const MoE::Recti& hitbox)
{
	for (auto& holders : m_BurgerHolders)
	{
		holders->CheckForCollision(hitbox);
	}
}

void LevelBurgers::CheckLevelCompleted()
{
	if (std::all_of(m_BurgerHolders.begin(), m_BurgerHolders.end(),
		[](const auto& holder)
		{
			return holder->IsHolderCompleted();
		}
	)) LevelManager::Get().Notify(nullptr, Event::levelCompleted);
}

void LevelBurgers::LoadBurgers(const std::string& loadPath, std::shared_ptr<MoE::Texture2D> texture)
{
	////// FILE STRUCTURE //////
	// nr of burgerHolders
	//
	// // nr of burgers
	// type X Y
	// type X Y
	// type X Y
	// 
	// // nr of burgers
	// type X Y
	// type X Y
	// etc....
	///////////////////////////

	m_BurgerHolders.clear();

	const std::string pathName{ MoE::ResourceManager::Get().GetFullPath(loadPath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELBURGERS::COULD_NOT_LOAD_BURGERS_FROM_FILE: " << pathName << "\n";
		return;
	}
	else
	{
		const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
		const int scaledTileSize{ tileSize * GameManager::Get().GetGameScale() };

		int nrHolders{};
		
		if (!(inFile >> nrHolders)) return;

		m_BurgerHolders.reserve(nrHolders);

		std::unique_ptr<MoE::GameObject> burgersRootObj{ std::make_unique<MoE::GameObject>() };
		MoE::GameObject* burgerRootObjPtr{ burgersRootObj.get() };
		GetOwner()->AddChild(std::move(burgersRootObj), true);

		for (int holderIdx{}; holderIdx < nrHolders; ++holderIdx)
		{
			int nrBurgers{};
			float holdHeight{};

			if (!(inFile >> nrBurgers >> holdHeight)) break;

			auto holder{ std::make_unique<BurgerHolder>(nrBurgers, static_cast<int>(holdHeight * scaledTileSize)) };

			for (int burgerIdx{}; burgerIdx < nrBurgers; ++burgerIdx)
			{
				int type{};
				int x{};
				int y{};

				if (!(inFile >> type >> x >> y)) break;

				// Create BurgerObject
				auto burgerObj{ std::make_unique<MoE::GameObject>() };

				// Create Burger Component And Add To Vector
				auto burger{ std::make_unique<Burger>(burgerObj.get(), texture, static_cast<int>(type), holder.get()) };

				// Set Correct Position
				const glm::vec2 pos
				{
					static_cast<float>(x * scaledTileSize),
					static_cast<float>((y * scaledTileSize) + (scaledTileSize / 2.f))
				};
				burgerObj->SetWorldPosition(pos);

				// Add pointer in holder
				holder->AddBurger(burger.get());

				// Add Component
				burgerObj->AddComponent(std::move(burger));

				// Make Child Of Burgers Root Object
				burgerRootObjPtr->AddChild(std::move(burgerObj), true);
			}

			// Add Pointer to vector
			m_BurgerHolders.emplace_back(std::move(holder));
		}
	}
}