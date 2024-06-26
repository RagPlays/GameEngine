#include <iostream>
#include <fstream>
#include <limits>

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
	, m_MoveOffset{}
	, m_StartPos{}
	, m_LinesX{}
	, m_LinesY{}
{
	LoadCollision(collisionLoadPath);
}

#if defined _DEBUG || defined DEBUG
void LevelCollision::Render() const
{
	Renderer& renderer{ Renderer::Get() };
	renderer.SetCurrentDrawColor(MoE::Color{ 255, 0, 0 });
	for (auto& linex : m_LinesX)
	{
		renderer.RenderLine(linex);
	}
	renderer.SetCurrentDrawColor(MoE::Color{ 255, 255, 0 });
	for (auto& liney : m_LinesY)
	{
		renderer.RenderLine(liney);
	}
}
#endif

const glm::vec2& LevelCollision::GetStartPos() const
{
	return m_StartPos;
}

int LevelCollision::GetMoveOffset() const
{
	return m_MoveOffset;
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
		start = glm::ivec2{ moveRect.pos.x + (moveDir.x > 0 ? moveRect.size.x : 0), moveRect.pos.y };
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

		if (CanMoveY(checkLine, hitLine))
		{
			moveRect.pos.y = static_cast<int>(playerPos.y);
			moveRect.size.y = hitbox.y;
			start = glm::ivec2{ moveRect.pos.x, moveRect.pos.y + (moveDir.y > 0 ? moveRect.size.y : 0) };
			line = Linei{ start, start + glm::ivec2{ moveRect.size.x, 0 } };
			return CanMoveY(hitLine, line, player, hitbox);
		}
	}
	return false;
}

MoveResult LevelCollision::CanMove(const glm::vec2& pos, const glm::ivec2& dir, const glm::ivec2& hitbox, bool enemy)
{
	const float moveOffset{ (enemy) ? static_cast<float>(m_MoveOffset * 0.5f) : static_cast<float>(m_MoveOffset) };

	Recti moveRect
	{
		static_cast<glm::ivec2>((pos + (static_cast<glm::vec2>(hitbox) * 0.5f)) - static_cast<float>(moveOffset) * 0.5f),
		glm::ivec2{ moveOffset, moveOffset }
	};

	glm::ivec2 start{};
	Linei line{};

	if (dir.x)
	{
		moveRect.pos.x = static_cast<int>(pos.x);
		moveRect.size.x = hitbox.x;
		start = glm::ivec2{ moveRect.pos.x + (dir.x > 0 ? moveRect.size.x : 0), moveRect.pos.y };
		line = Linei{ start, start + glm::ivec2{ 0, moveRect.size.y } }; // left or right line
		return CanMoveX(line);
	}
	else if (dir.y)
	{
		moveRect.pos.y = static_cast<int>(pos.y);
		moveRect.size.y = hitbox.y;
		start = glm::ivec2{ moveRect.pos.x, moveRect.pos.y + (dir.y > 0 ? moveRect.size.y : 0) };
		line = Linei{ start, start + glm::ivec2{ moveRect.size.x, 0 } }; // top or bot line
		return CanMoveY(line, pos, hitbox);
	}
	return { false, Linei{} };
}

int LevelCollision::GetNextBurgerFallPos(const glm::ivec2& pos) const
{
	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) * GameManager::Get().GetGameScale() };
	const int yOffset{ static_cast<int>(0.25f * tileSize) };
	const int yPos{ pos.y };

	for (const auto& lineX : m_LinesX)
	{
		const int fallPos{ lineX.pointOne.y + yOffset };
		if (fallPos > yPos)
		{
			if (IsBetween(pos.x, lineX.pointOne.x, lineX.pointTwo.x))
			{
				return fallPos;
			}
		}
	}
	return std::numeric_limits<int>::max();
}

bool LevelCollision::IsBetween(int x, int x1, int x2)
{
	return (x > std::min(x1, x2) && x < std::max(x1, x2));
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
			const int scale{ GameManager::Get().GetGameScale() };
			tileSize = static_cast<int>(LevelManager::Get().GetTileSize()) * scale;
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

MoveResult LevelCollision::CanMoveX(const MoE::Linei& leftOrRight)
{
	for (const Linei& lineX : m_LinesX)
	{
		if (Coll::LinesIntersecting(lineX, leftOrRight)) return { true, lineX };
	}
	return { false, Linei{} };
}

MoveResult LevelCollision::CanMoveY(const MoE::Linei& topOrBot, const glm::vec2& pos, const glm::ivec2& hitbox)
{
	for (const Linei& lineY : m_LinesY)
	{
		if (Coll::LinesIntersecting(lineY, topOrBot))
		{
			const int midY{ static_cast<int>(pos.y) + static_cast<int>(hitbox.y * 0.5f) };
			if(IsBetween(midY, lineY.pointOne.y, lineY.pointTwo.y)) return { true, lineY };
		}
	}
	return { false, Linei{} };
}