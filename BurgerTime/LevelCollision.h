#ifndef LEVELCOLLISION_H
#define LEVELCOLLISION_H

#include <vector>
#include <string>
#include "Component.h"
#include "PlayerComponent.h"
#include "Structs.h"

class LevelCollision final : public Component
{
public:

	LevelCollision(GameObject* const owner, const std::string& collisionLoadPath);
	~LevelCollision() = default;

	virtual void GameStart() override;

private:

	bool HitTopOrBot(const Linef& line, const Rectf& rect);
	bool HitLeftOrRight(const Linef& line, const Rectf& rect);
	bool LineHitLine(const Linef& firstLine, const Linef& secondLine);

private:

	const std::string m_FilePath;

	std::vector<Linef> m_LinesX;
	std::vector<Linef> m_LinesY;

};

#endif // !LEVELCOLLISION_H