#include <iostream>
#include <fstream>

#include "LevelBurgers.h"
#include "Burger.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "GameObject.h"

LevelBurgers::LevelBurgers(MoE::GameObject* const owner, const std::string& burgerLoadPath, std::shared_ptr<MoE::Texture2D> texture)
	: MoE::Component{ owner }
	, m_Burgers{}
	, m_Texture{ texture }
{
	LoadBurgers(burgerLoadPath);
}

LevelBurgers::~LevelBurgers() = default;

void LevelBurgers::Render() const
{
	for (const auto& burger : m_Burgers)
	{
		burger->Render();
	}
}

void LevelBurgers::CheckForCollision(const MoE::Recti& hitbox)
{
	for (auto& burger : m_Burgers)
	{
		burger->CheckForCollision(static_cast<MoE::Rectf>(hitbox));
	}
}

void LevelBurgers::LoadBurgers(const std::string& loadPath)
{
	////// FILE STRUCTURE //////
	// nr of burgers
	//
	// type X Y
	// type X Y
	// type X Y
	// type X Y
	// etc....
	///////////////////////////

	m_Burgers.clear();

	const std::string pathName{ MoE::ResourceManager::Get().GetFullPath(loadPath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELBURGERS::COULD_NOT_LOAD_BURGERS_FROM_FILE: " << pathName << "\n";
		return;
	}
	else
	{
		const int tileSize{ LevelManager::Get().GetTileSize() };
		const int scaledTileSize{ tileSize * GameManager::Get().GetGameScale() };

		int nrBurgers{};

		if (inFile >> nrBurgers)
		{
			m_Burgers.reserve(nrBurgers);
		}
		else return;

		int type{};
		int x{};
		int y{};

		std::unique_ptr<MoE::GameObject> burgersRootObj{ std::make_unique<MoE::GameObject>() };

		while (inFile >> type >> x >> y)
		{
			// Create BurgerObject
			std::unique_ptr<MoE::GameObject> burgerObj{ std::make_unique<MoE::GameObject>() };
			MoE::GameObject* burgerObjPtr{ burgerObj.get() };

			// Create Burger Component And Add To Vector
			std::unique_ptr<Burger> burger{ std::make_unique<Burger>(burgerObjPtr, m_Texture, static_cast<int>(type)) };
			Burger* burgerPtr{ burger.get() };

			// Add Component
			burgerObj->AddComponent(std::move(burger));
			
			// Add Pointer to vector
			m_Burgers.emplace_back(burgerPtr);

			// Make Child Of Burgers Root Object
			burgersRootObj->AddChild(std::move(burgerObj));

			// Set Correct Position
			const glm::vec2 pos
			{
				static_cast<float>(x * scaledTileSize),
				static_cast<float>((y * scaledTileSize) + (scaledTileSize / 2.f))
			};
			burgerObjPtr->SetWorldPosition(pos);
		}

		GetOwner()->AddChild(std::move(burgersRootObj));
	}
}