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
class BurgerHolder;

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

#if defined DEBUG || defined _DEBUG
	virtual void Render() const;
#endif

	void CheckForCollision(const MoE::Recti& hitbox);

	void CheckLevelCompleted();

private:

	void LoadBurgers(const std::string& loadPath, std::shared_ptr<MoE::Texture2D> texture);

private:

	std::vector<std::unique_ptr<BurgerHolder>> m_BurgerHolders;

};

#endif // !LEVELBURGERS_H
