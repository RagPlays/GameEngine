#include <iostream>
#include <fstream>

#include "LevelCollision.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "PlayerMovement.h"
#include "GameManager.h"
#include "LevelManager.h"

LevelCollision::LevelCollision(GameObject* const owner, const std::string& collisionLoadPath)
	: Component{ owner }
{
	LoadCollision(collisionLoadPath);
}

const glm::vec2& LevelCollision::GetStartPos() const
{
	return m_StartPos;
}

bool LevelCollision::CanMove(PlayerMovement* playerMovement)
{
	const glm::ivec2& moveDir{ playerMovement->GetMoveDir() };
	const glm::ivec2& hitbox{ playerMovement->GetHitBox() };
	const glm::vec2& playerPos{ playerMovement->GetPosition() };

	Recti playerMoveCheckRect
	{
		static_cast<glm::ivec2>((playerPos + (static_cast<glm::vec2>(hitbox) * 0.5f)) - static_cast<float>(m_MoveOffset) * 0.5f),
		glm::ivec2{ m_MoveOffset, m_MoveOffset }
	};

	if (moveDir.x)
	{
		playerMoveCheckRect.pos.x = static_cast<int>(playerPos.x);
		playerMoveCheckRect.size.x = hitbox.x;
		const glm::ivec2 start
		{ 
			playerMoveCheckRect.pos.x + (moveDir.x > 0 ? playerMoveCheckRect.size.x : 0),
			playerMoveCheckRect.pos.y
		};
		const Linei line
		{
			start,
			start + glm::ivec2{ 0, playerMoveCheckRect.size.y }
		};
		return CanMoveX(line, playerMovement);
	}
	else if (moveDir.y)
	{
		playerMoveCheckRect.pos.y = static_cast<int>(playerPos.y);
		playerMoveCheckRect.size.y = hitbox.y;
		const glm::ivec2 start
		{
			playerMoveCheckRect.pos.x,
			playerMoveCheckRect.pos.y + (moveDir.y > 0 ? playerMoveCheckRect.size.y : 0)
		};
		const Linei line
		{
			start,
			start + glm::ivec2{ playerMoveCheckRect.size.x, 0 }
		};
		return CanMoveY(line, playerMovement);
	}
	return false;
}

void LevelCollision::LoadCollision(const std::string& filePath)
{
	m_LinesX.clear();
	m_LinesY.clear();

	////// FILE STRUCTURE //////
	// startPosX startPosY
	// aprroximate LineX size
	// aprroximate LineY size
	// moveoffset
	// tile size
	// 
	// x1 y1 x2 y2
	// x1 y1 x2 y2
	// x1 y1 x2 y2
	// x1 y1 x2 y2
	// .......
	////////////////////////////

	const std::string pathName{ ResourceManager::Get().GetFullPath(filePath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELCOLLISION::COULD_NOT_LOAD_COLLISIONS_FROM_FILE: " << pathName << "\n";
		return;
	}
	else
	{
		int tileSize{};

		float startTileX{};
		float startTileY{};
		int approximateLineXSize{};
		int approximateLineYSize{};
		float moveOffset{};

		if (inFile >> startTileX >> startTileY >> approximateLineXSize >> approximateLineYSize >> moveOffset)
		{
			tileSize = static_cast<int>(LevelManager::Get().GetTileSize() * GameManager::Get().GetGameScale());
			m_StartPos = glm::vec2
			{
				startTileX * static_cast<float>(tileSize),
				(startTileY - 0.25f) * static_cast<float>(tileSize)
			};
			m_LinesX.reserve(static_cast<size_t>(approximateLineXSize));
			m_LinesY.reserve(static_cast<size_t>(approximateLineYSize));
			m_MoveOffset = static_cast<int>(moveOffset * tileSize);
		}
		else return;

		float p1x{};
		float p1y{};
		float p2x{};
		float p2y{};

		constexpr float epsilon{ 0.001f };

		while (inFile >> p1x >> p1y >> p2x >> p2y)
		{
			if (inFile)
			{
				if (std::abs(p1y - p2y) < epsilon) // LineX
				{
					const int po1X{ static_cast<int>(p1x * tileSize) };
					const int po1Y{ static_cast<int>((p1y - 0.75f) * tileSize) };
					const int po2X{ static_cast<int>(p2x * tileSize) };
					const int po2Y{ static_cast<int>((p2y - 0.75f) * tileSize) };
					m_LinesX.emplace_back(Linei{ glm::ivec2{ po1X, po1Y }, glm::ivec2{ po2X, po2Y } });
				}
				else if (std::abs(p1x - p2x) < epsilon) // LineY
				{
					const int po1X{ static_cast<int>(p1x * tileSize) };
					const int po1Y{ static_cast<int>((p1y - 0.25f) * tileSize) };
					const int po2X{ static_cast<int>(p2x * tileSize) };
					const int po2Y{ static_cast<int>((p2y - 0.25f) * tileSize) };
					m_LinesY.emplace_back(Linei{ glm::ivec2{ po1X, po1Y }, glm::ivec2{ po2X, po2Y } });
				}
				else
				{
					std::cerr << "ERROR::LEVELCOLLISION::COLLISIONFILE_NOT_SET_CORRECTLY!\n";
					std::cout << "Values: " << p1x << " " << p1y << " " << p2x << " " << p2y << "\n";
				}
			}
			else return;
		}
	}
}

bool LevelCollision::CanMoveX(const Linei& leftOrRight, PlayerMovement* playerMovement) const
{
	const glm::ivec2& hitbox{ playerMovement->GetHitBox() };
	const glm::vec2& pos{ playerMovement->GetPosition() };

	for (const auto& line : m_LinesX)
	{
		if (LineHitLine(leftOrRight, line))
		{
			playerMovement->SetPosition(
				glm::vec2
				{
					pos.x,
					static_cast<float>(line.pointOne.y) - static_cast<float>(hitbox.y) * 0.5f
				}
			);
			return true;
		}
	}
	return false;
}

bool LevelCollision::CanMoveY(const Linei& topOrBot, PlayerMovement* playerMovement) const
{
	const glm::ivec2& hitbox{ playerMovement->GetHitBox() };
	const glm::vec2& pos{ playerMovement->GetPosition() };

	for (const auto& line : m_LinesY)
	{
		if (LineHitLine(topOrBot, line))
		{
			playerMovement->SetPosition(
				glm::vec2
				{ 
					static_cast<float>(line.pointOne.x) - static_cast<float>(hitbox.x) * 0.5f,
					pos.y 
				}
			);
			return true;
		}
	}
	return false;
}

bool LevelCollision::LineHitLine(const Linei& firstLine, const Linei& secondLine) const
{
	const glm::ivec2& p1{ firstLine.pointOne };
	const glm::ivec2& p2{ firstLine.pointTwo };
	const glm::ivec2& p3{ secondLine.pointOne };
	const glm::ivec2& p4{ secondLine.pointTwo };

	const float denominator{ 1.f / static_cast<float>((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y)) };

	const float uA
	{
		static_cast<float>((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
		*
		denominator
	};

	const float uB
	{
		static_cast<float>((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
		*
		denominator
	};

	return (uA >= 0.f && uA <= 1.f && uB >= 0.f && uB <= 1.f);
}