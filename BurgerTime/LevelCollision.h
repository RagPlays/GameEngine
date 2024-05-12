#ifndef LEVELCOLLISION_H
#define LEVELCOLLISION_H

#include <vector>
#include <string>

#include "Component.h"
#include "Structs.h" // 'Linef' and 'Rectf'

class PlayerMovement;

class LevelCollision final : public Component
{
public:

	explicit LevelCollision(GameObject* const owner, const std::string& collisionLoadPath);
	virtual ~LevelCollision() = default;

	const glm::vec2& GetStartPos() const;

	bool CanMove(PlayerMovement* playerMovement);

private:

	void LoadCollision(const std::string& filePath);

	bool CanMoveX(const Linei& leftOrRight, PlayerMovement* playerMovement) const;
	bool CanMoveY(const Linei& topOrBot, PlayerMovement* playerMovement) const;
	bool LineHitLine(const Linei& firstLine, const Linei& secondLine) const;

private:

	int m_MoveOffset;
	glm::vec2 m_StartPos;
	std::vector<Linei> m_LinesX;
	std::vector<Linei> m_LinesY;

};

#endif // !LEVELCOLLISION_H