#ifndef ENEMY_H
#define ENEMY_H

#include "Component.h"
#include "Structs.h"

namespace MoE
{
	class GameObject;
	class TextureRenderer;

	struct Rectf;
	struct Recti;
}

class Player;
class EnemyStateHandler;

enum class EnemyType
{
	hotdog = 0,
	pickle,
	egg
};

class Enemy : public MoE::Component
{
public:

	explicit Enemy(MoE::GameObject* const owner, EnemyType type, const glm::vec2& startPos, const glm::ivec2& startDir);
	virtual ~Enemy() = default;

	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) noexcept = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void FixedUpdate() override;

#if defined DEBUG || defined _DEBUG
	virtual void Render() const override;
#endif

	void CheckForCollision(const MoE::Recti& burgerColl);
	void CheckForCollision(Player* player);

	void GoEndState();
	void Respawn();

	EnemyType GetType() const;
	const glm::ivec2& GetStartDir() const;

private:

	const glm::vec2 m_StartPos;
	const glm::ivec2 m_StartDir;
	MoE::Recti m_Hitbox;
	EnemyType m_Type;

	// Componentns
	MoE::TextureRenderer* m_pRenderComp;
	EnemyStateHandler* m_pStateHandler;

};

#endif // !ENEMY_H
