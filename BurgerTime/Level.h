#ifndef LEVEL_H
#define LEVEL_H

#include "Component.h"

class LevelCollision;
class LevelRenderer;

class Level final : public Component
{
public:

	Level() = default;
	~Level() = default;

private:

	Level* m_pLevel;
	LevelCollision* m_pLevelCollision;
	LevelRenderer* m_pLevelRenderer;

};

#endif // !LEVEL_H
