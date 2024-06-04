#ifndef ENEMYPLAYER_H
#define ENEMYPLAYER_H

#include "Component.h"

class EnemyPlayer final : public MoE::Component
{
public:

	EnemyPlayer(const EnemyPlayer& other) = delete;
	EnemyPlayer(EnemyPlayer&& other) noexcept = delete;
	EnemyPlayer& operator=(const EnemyPlayer& other) = delete;
	EnemyPlayer& operator=(EnemyPlayer&& other) noexcept = delete;

private:

};

#endif // !ENEMYPLAYER_H
