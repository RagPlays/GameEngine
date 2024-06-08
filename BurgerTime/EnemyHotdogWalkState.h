#ifndef ENEMYHOTDOGWALKSTATE_H
#define ENEMYHOTDOGWALKSTATE_H

#include <glm.hpp>

#include "EnemyState.h"

class EnemyHotdogWalkState final : public EnemyState
{
public:

private:

	glm::ivec2 m_MoveDir;

};

#endif // !ENEMYHOTDOGWALKSTATE_H
