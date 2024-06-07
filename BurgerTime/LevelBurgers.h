#ifndef LEVELBURGERS_H
#define LEVELBURGERS_H

#include <vector>
#include <string>
#include <memory>

#include "Component.h"

namespace MoE
{
	class Texture2D;
	class GameObject;

	struct Recti;
}

class Player;
class Burger;

enum class BurgerPartType
{
	topBun = 0,
	botBun,
	chees,
	patty,
	tomato,
	lettuce
};

class LevelBurgers final : public MoE::Component
{
public:
	
	explicit LevelBurgers(MoE::GameObject* const owner, const std::string& burgerLoadPath, std::shared_ptr<MoE::Texture2D> texture);
	virtual ~LevelBurgers();

	LevelBurgers(const LevelBurgers& other) = delete;
	LevelBurgers(LevelBurgers&& other) noexcept = delete;
	LevelBurgers& operator=(const LevelBurgers& other) = delete;
	LevelBurgers& operator=(LevelBurgers&& other) noexcept = delete;

	virtual void Render() const override;

	void CheckForCollision(const MoE::Recti& hitbox);

private:

	void LoadBurgers(const std::string& loadPath);

private:

	// all burgers are owned by the owner of this component
	std::vector<Burger*> m_Burgers;

	std::shared_ptr<MoE::Texture2D> m_Texture;

};

#endif // !LEVELBURGERS_H
