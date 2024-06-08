#ifndef LEVELENEMIES_H
#define LEVELENEMIES_H

#include <memory>
#include <vector>
#include <string>

#include "Component.h"

namespace MoE
{
	class GameObject;
	class Texture2D;

	struct Rectf;
	struct Recti;
}

class Enemy;

class LevelEnemies final : public MoE::Component
{
public:

	explicit LevelEnemies(MoE::GameObject* const owner, const std::string& loadPath, std::shared_ptr<MoE::Texture2D> texture);
	virtual ~LevelEnemies() = default;

	void CheckForCollision(const MoE::Recti& burgerColl);

private:

	void LoadEnemies(const std::string& loadPath, std::shared_ptr<MoE::Texture2D> texture);

private:

	std::vector<Enemy*> m_Enemies;

};

#endif // !LEVELENEMIES_H
