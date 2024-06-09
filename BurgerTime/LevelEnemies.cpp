#include <iostream>
#include <fstream>

#include "LevelEnemies.h"
#include "Enemy.h"
#include "EnemyState.h"
#include "EnemyStateHandler.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "TextureRenderer.h"

using namespace MoE;

LevelEnemies::LevelEnemies(GameObject* const owner, const std::string& loadPath, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
{
	LoadEnemies(loadPath, texture);
}

void LevelEnemies::CheckForCollision(const Recti& burgerColl)
{
	for (auto& enemy : m_Enemies)
	{
		enemy->CheckForCollision(burgerColl);
	}
}

void LevelEnemies::CheckForCollision(Player* player)
{
	for (auto& enemy : m_Enemies)
	{
		enemy->CheckForCollision(player);
	}
}

void LevelEnemies::GoEndState()
{
	for (auto& enemy : m_Enemies)
	{
		enemy->GoEndState();
	}
}

void LevelEnemies::Respawn()
{
	for (auto& enemy : m_Enemies)
	{
		enemy->Respawn();
	}
}

void LevelEnemies::LoadEnemies(const std::string& filePath, std::shared_ptr<Texture2D> texture)
{
	m_Enemies.clear();

	////// FILE STRUCTURE //////
	// nrOfEnemies
	//
	// type startX startY startDirX startDirY
	// type startX startY startDirX startDirY
	// type startX startY startDirX startDirY
	// type startX startY startDirX startDirY
	// etc...
	////////////////////////////

	const std::string pathName{ ResourceManager::Get().GetFullPath(filePath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELENEMIES::COULD_NOT_LOAD_ENEMIES_FROM_FILE: " << pathName << "\n";
		return;
	}
	else
	{
		int nrOfEnemies{};
		if (!(inFile >> nrOfEnemies)) return;

		m_Enemies.reserve(nrOfEnemies);

		std::unique_ptr<MoE::GameObject> enemiesRootObj{ std::make_unique<MoE::GameObject>() };
		MoE::GameObject* enemiesRootObjPtr{ enemiesRootObj.get() };
		GetOwner()->AddChild(std::move(enemiesRootObj), true);

		const int scale{ GameManager::Get().GetGameScale() };
		const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
		const int renderTileSize{ tileSize * scale };

		int type{};
		int startX{};
		int startY{};
		int startDirX{};
		int startDirY{};

		while (inFile >> type >> startX >> startY >> startDirX >> startDirY)
		{
			auto enemyObj{ std::make_unique<GameObject>() };

			const glm::vec2 startPos
			{
				startX* static_cast<float>(renderTileSize),
				(startY - 0.25f) * static_cast<float>(renderTileSize)
			};
			const glm::ivec2 startDir{ startDirX, startDirY };

			// Create Components
			auto enemyRenderComp{ std::make_unique<TextureRenderer>(enemyObj.get(), texture) };
			auto enemy{ std::make_unique<Enemy>(enemyObj.get(), static_cast<EnemyType>(type), startPos, startDir) };
			auto enemyStateHandler{ std::make_unique<EnemyStateHandler>(enemyObj.get(), enemy.get()) };

			// Set Enemy Pointer In Vector
			m_Enemies.emplace_back(enemy.get());

			// Add Components
			enemyObj->AddComponent(std::move(enemyRenderComp));
			enemyObj->AddComponent(std::move(enemy));
			enemyObj->AddComponent(std::move(enemyStateHandler));

			// Set Enemy Child To EnemiesRootObj
			enemiesRootObjPtr->AddChild(std::move(enemyObj), true);
		}
	}
}