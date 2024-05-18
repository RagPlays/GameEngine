#ifndef LEVELCOLLISION_H
#define LEVELCOLLISION_H

#include <vector>
#include <string>

#include "Component.h"
#include "Structs.h" // 'Linef' and 'Rectf'

class Player;

class LevelCollision final : public MoE::Component
{
public:

	explicit LevelCollision(MoE::GameObject* const owner, const std::string& collisionLoadPath);
	virtual ~LevelCollision() = default;

	const glm::vec2& GetStartPos() const;

	bool CanMove(Player* player, const glm::ivec2& moveHitBox);

private:

	void LoadCollision(const std::string& filePath);

	bool CanMoveX(const MoE::Linei& leftOrRight, Player* player, const glm::ivec2& hitbox) const;
	bool CanMoveY(const MoE::Linei& topOrBot, Player* player, const glm::ivec2& hitbox) const;
	bool LineHitLine(const MoE::Linei& firstLine, const MoE::Linei& secondLine) const;

private:

	int m_MoveOffset;
	glm::vec2 m_StartPos;
	std::vector<MoE::Linei> m_LinesX;
	std::vector<MoE::Linei> m_LinesY;

};

#endif // !LEVELCOLLISION_H