#ifndef ENEMY_H
#define ENEMY_H

#include "Component.h"
#include "Structs.h"

namespace MoE
{
	class GameObject;

	struct Rectf;
	struct Recti;
}

enum class EnemyType
{
	hotdog,
	egg,
	pickle
};

class Enemy : MoE::Component
{
public:

	explicit Enemy(MoE::GameObject* const owner, EnemyType type);
	virtual ~Enemy() = default;

	virtual void SceneStart() override;
	virtual void FixedUpdate() override;

	EnemyType GetType() const;

private:

	MoE::Recti m_Hitbox;
	EnemyType m_Type;

};

#endif // !ENEMY_H
