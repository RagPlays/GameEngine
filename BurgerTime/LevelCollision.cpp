#include <iostream>
#include "LevelCollision.h"
#include "GameObject.h"
#include "SceneManager.h"

LevelCollision::LevelCollision(GameObject* const owner, const std::string& collisionLoadPath)
	: Component{ owner }
	, m_FilePath{ collisionLoadPath }
{
	m_LinesX.clear();
	m_LinesY.clear();

	// MovementBox and a DamageHitBox

	//Rectf playerRect{ glm::ivec2{ 50, 50 }, glm::ivec2{ 10, 10 } };

	//const Line hitLineX{ 55, 0, 300 }; // right through
	//const Line misLineX{ 60, 20, 80 };
	//const Line hitLineY{ 59, 0, 300 }; // just in
	//const Line misLineY{ 15, 0, 300 };

	/*bool line1{ HitTopOrBot(hitLineX, playerRect) };
	bool line2{ HitTopOrBot(misLineX, playerRect) };
	bool line3{ HitLeftOrRight(hitLineY, playerRect) };
	bool line4{ HitLeftOrRight(misLineY, playerRect) };

	if (line1) return;
	if (line2) return;
	if (line3) return;
	if (line4) return;*/
}

void LevelCollision::GameStart()
{
	//GameObject::Destroy(GetOwner()); // Destroy itself
	SceneManager::Get().SetCurrentSceneByIndex(1);
}

bool LevelCollision::HitTopOrBot(const Linef& line, const Rectf& rect)
{
	const Linef top
	{
		rect.pos,
		glm::vec2{ rect.pos.x + rect.size.x, rect.pos.y }
	};
	const Linef bot
	{
		glm::vec2{ rect.pos.x, rect.pos.y + rect.size.y },
		glm::vec2{ rect.pos.x + rect.size.x, rect.pos.y + rect.size.y }
	};
	return (LineHitLine(line, top) || LineHitLine(line, bot));
}

bool LevelCollision::HitLeftOrRight(const Linef& line, const Rectf& rect)
{
	const Linef left
	{ 
		rect.pos,
		glm::vec2{ rect.pos.x, rect.pos.y + rect.size.y }
	};
	const Linef right
	{ 
		glm::vec2{ rect.pos.x + rect.size.x, rect.pos.y },
		glm::vec2{ rect.pos.x + rect.size.x, rect.pos.y + rect.size.y }
	};
	return (LineHitLine(line, left) || LineHitLine(line, right));
}

bool LevelCollision::LineHitLine(const Linef& firstLine, const Linef& secondLine)
{
	const glm::vec2& p1{ firstLine.pointOne };
	const glm::vec2& p2{ firstLine.pointTwo };
	const glm::vec2& p3{ secondLine.pointOne };
	const glm::vec2& p4{ secondLine.pointTwo };

	const float uA
	{
		((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
		/
		((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y))
	};

	const float uB
	{
		((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
		/
		((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y))
	};

	return (uA >= 0.f && uA <= 1.f && uB >= 0.f && uB <= 1.f);
}