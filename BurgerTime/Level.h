#ifndef LEVEL_H
#define LEVEL_H

#include "Component.h"

namespace MoE
{
	class GameObject;
}

class LevelCollision;
class LevelRenderer;

class Level final : public MoE::Component
{
public:

	explicit Level(MoE::GameObject* const owner);
	virtual ~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

};

#endif // !LEVEL_H
