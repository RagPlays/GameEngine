#include <iostream>
#include <fstream>

#include "LevelCollision.h"
#include "Collisions.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Player.h"
#include "GameManager.h"
#include "LevelManager.h"

#if defined DEBUG || defined _DEBUG
#include "Renderer.h"
#endif

using namespace MoE;

LevelCollision::LevelCollision(GameObject* const owner, const std::string& collisionLoadPath)
	: Component{ owner }
{
	LoadCollision(collisionLoadPath);
}

void LevelCollision::Render() const
{
#if defined DEBUG || defined _DEBUG
	Renderer& renderer{ Renderer::Get() };
	renderer.SetCurrentDrawColor(MoE::Color{ 255, 0, 0, 255 });
	for (auto& linex : m_LinesX)
	{
		renderer.RenderLine(linex);
	}
	renderer.SetCurrentDrawColor(MoE::Color{ 255, 255, 0, 255 });
	for (auto& liney : m_LinesY)
	{
		renderer.RenderLine(liney);
	}
#endif
}

const glm::vec2& LevelCollision::GetStartPos() const
{
	return m_StartPos;
}

bool LevelCollision::CanMove(Player* player, const glm::ivec2& moveHitBox)
{
	const glm::ivec2& moveDir{ player->GetMoveDir() };
	const glm::ivec2& hitbox{ moveHitBox };
	const glm::vec2& playerPos{ player->GetOwner()->GetLocalPosition() };

	Recti moveRect
	{
		static_cast<glm::ivec2>((playerPos + (static_cast<glm::vec2>(hitbox) * 0.5f)) - static_cast<float>(m_MoveOffset) * 0.5f),
		glm::ivec2{ m_MoveOffset, m_MoveOffset }
	};

	glm::ivec2 start{};
	Linei line{};

	if (moveDir.x)
	{
		moveRect.pos.x = static_cast<int>(playerPos.x);
		moveRect.size.x = hitbox.x;
		start = { moveRect.pos.x + (moveDir.x > 0 ? moveRect.size.x : 0), moveRect.pos.y };
		line = Linei{ start, start + glm::ivec2{ 0, moveRect.size.y } };
		return CanMoveX(line, player, hitbox);
	}
	else if (moveDir.y)
	{
		const MoE::Linei checkLine
		{
			moveDir.y < 0 ? moveRect.pos : glm::ivec2{ moveRect.pos.x, moveRect.pos.y + moveRect.size.y },
			glm::ivec2{ moveRect.pos.x + moveRect.size.x, moveRect.pos.y + (moveDir.y < 0 ? 0 : moveRect.size.y) }
		};

		Linei hitLine{};

		if (!CanMoveY(checkLine, hitLine)) return false;

		moveRect.pos.y = static_cast<int>(playerPos.y);
		moveRect.size.y = hitbox.y;
		start = { moveRect.pos.x, moveRect.pos.y + (moveDir.y > 0 ? moveRect.size.y : 0) };
		line = Linei{ start, start + glm::ivec2{ moveRect.size.x, 0 } };
		return CanMoveY(hitLine, line, player, hitbox);
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

bool LevelCollision::CanMoveX(const Linei& leftOrRight, Player* player, const glm::ivec2& hitbox) const
{
	const glm::vec2& pos{ player->GetOwner()->GetLocalPosition() };

	for (const Linei& linex : m_LinesX)
	{
		if (Coll::LinesIntersecting(linex, leftOrRight))
		{
			player->GetOwner()->SetLocalPosition(
				glm::vec2
				{
					pos.x,
					static_cast<float>(linex.pointOne.y) - static_cast<float>(hitbox.y) * 0.5f
				}
			);
			return true;
		}
	}
	return false;
}

bool LevelCollision::CanMoveY(const MoE::Linei& line, MoE::Linei& hitLine) const
{
	for (const Linei& liney : m_LinesY)
	{
		if (Coll::LinesIntersecting(liney, line))
		{
			hitLine = liney;
			return true;
		}
	}
	return false;
}

bool LevelCollision::CanMoveY(const Linei& hitLine, const Linei& topOrBot, Player* player, const glm::ivec2& hitbox) const
{
	const glm::vec2& pos{ player->GetOwner()->GetLocalPosition() };

	if (Coll::LinesIntersecting(hitLine, topOrBot))
	{
		player->GetOwner()->SetLocalPosition(
			glm::vec2
			{
				static_cast<float>(hitLine.pointOne.x) - static_cast<float>(hitbox.x) * 0.5f,
				pos.y
			}
		);
		return true;
	}
	return false;
}

//bool LevelCollision::LineHitLine(const Linei& firstLine, const Linei& secondLine) const
//{
//	const glm::ivec2& p1{ firstLine.pointOne };
//	const glm::ivec2& p2{ firstLine.pointTwo };
//	const glm::ivec2& p3{ secondLine.pointOne };
//	const glm::ivec2& p4{ secondLine.pointTwo };
//
//	const float denominator{ 1.f / static_cast<float>((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y)) };
//
//	const float uA
//	{
//		static_cast<float>((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
//		*
//		denominator
//	};
//
//	const float uB
//	{
//		static_cast<float>((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
//		*
//		denominator
//	};
//
//	return (uA >= 0.f && uA <= 1.f && uB >= 0.f && uB <= 1.f);
//}