#ifndef LEVEL_H
#define LEVEL_H

#include "Component.h"

class LevelCollision;
class LevelRenderer;
class GameObject;

class Level final : public Component
{
public:

	explicit Level(GameObject* const owner);
	virtual ~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

};

#endif // !LEVEL_H
