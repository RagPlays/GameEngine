#ifndef LEVELCOLLISION_H
#define LEVELCOLLISION_H

#include <vector>
#include <string>

#include "Component.h"
#include "Structs.h" // 'Linef' and 'Rectf'

class Player;
class Enemy;

struct MoveResult
{
	bool canMove;
	MoE::Linei line;
};

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
	MoveResult CanMove(const glm::vec2& pos, const glm::ivec2& dir, const glm::ivec2& hitbox, bool enemy);

	int GetNextBurgerFallPos(const glm::ivec2& pos) const;

	static bool IsBetween(int x, int x1, int x2);

private:

	void LoadCollision(const std::string& filePath);

	bool CanMoveX(const MoE::Linei& leftOrRight, Player* player, const glm::ivec2& hitbox) const;
	bool CanMoveY(const MoE::Linei& line, MoE::Linei& hitLine) const;
	bool CanMoveY(const MoE::Linei& hitLine, const MoE::Linei& topOrBot, Player* player, const glm::ivec2& hitbox) const;

	MoveResult CanMoveX(const MoE::Linei& leftOrRight);
	MoveResult CanMoveY(const MoE::Linei& topOrBot, const glm::vec2& pos, const glm::ivec2& hitbox);

private:

	int m_MoveOffset;
	glm::vec2 m_StartPos;
	std::vector<MoE::Linei> m_LinesX;
	std::vector<MoE::Linei> m_LinesY;

};

#endif // !LEVELCOLLISION_H