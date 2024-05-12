#ifndef LEVELCOLLISION_H
#define LEVELCOLLISION_H

#include <vector>
#include <string>

#include "Component.h"
#include "Structs.h" // 'Linef' and 'Rectf'

class PlayerMovement;

class LevelCollision final : public MoE::Component
{
public:

	explicit LevelCollision(MoE::GameObject* const owner, const std::string& collisionLoadPath);
	virtual ~LevelCollision() = default;

	const glm::vec2& GetStartPos() const;

	bool CanMove(PlayerMovement* playerMovement);

private:

	void LoadCollision(const std::string& filePath);

	bool CanMoveX(const MoE::Linei& leftOrRight, PlayerMovement* playerMovement) const;
	bool CanMoveY(const MoE::Linei& topOrBot, PlayerMovement* playerMovement) const;
	bool LineHitLine(const MoE::Linei& firstLine, const MoE::Linei& secondLine) const;

private:

	int m_MoveOffset;
	glm::vec2 m_StartPos;
	std::vector<MoE::Linei> m_LinesX;
	std::vector<MoE::Linei> m_LinesY;

};

#endif // !LEVELCOLLISION_H