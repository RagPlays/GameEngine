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

#if defined _DEBUG || defined DEBUG
	virtual void Render() const override;
#endif

	const glm::vec2& GetStartPos() const;
	int GetMoveOffset() const;

	bool CanMove(Player* player, const glm::ivec2& moveHitBox);

private:

	void LoadCollision(const std::string& filePath);

	bool CanMoveX(const MoE::Linei& leftOrRight, Player* player, const glm::ivec2& hitbox) const;
	bool CanMoveY(const MoE::Linei& line, MoE::Linei& hitLine) const;
	bool CanMoveY(const MoE::Linei& hitLine, const MoE::Linei& topOrBot, Player* player, const glm::ivec2& hitbox) const;

private:

	int m_MoveOffset;
	glm::vec2 m_StartPos;
	std::vector<MoE::Linei> m_LinesX;
	std::vector<MoE::Linei> m_LinesY;

};

#endif // !LEVELCOLLISION_H