#ifndef LEVELBURGERS_H
#define LEVELBURGERS_H

#include <vector>
#include <string>
#include <vector>
#include <memory>

#include "Component.h"

namespace MoE
{
	class GameManager;

	struct Recti;
}

class Player;
class Burger;

enum class BurgerPartType
{
	topBun,
	patty,
	chees,
	lettuce,
	tomato,
	botBun
};

class LevelBurgers final : MoE::Component
{
public:
	
	explicit LevelBurgers(MoE::GameObject* const owner, const std::string& burgerLoadPath);
	virtual ~LevelBurgers() = default;

	LevelBurgers(const LevelBurgers& other) = delete;
	LevelBurgers(LevelBurgers&& other) noexcept = delete;
	LevelBurgers& operator=(const LevelBurgers& other) = delete;
	LevelBurgers& operator=(LevelBurgers&& other) noexcept = delete;

	virtual void Render() const override;

	void UpdateCollision(const MoE::Recti& hitbox);

private:

	void LoadBurgers(const std::string& loadPath);

private:

	// all burgers are owned by the owner of this component
	std::vector<Burger*> m_Burgers;

};

#endif // !LEVELBURGERS_H
