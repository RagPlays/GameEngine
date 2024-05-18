//#ifndef PLAYERMOVEMENTCOMPONENT_H
//#define PLAYERMOVEMENTCOMPONENT_H
//
//#include "Component.h"
//
//class PlayerMovement final : public MoE::Component
//{
//public:
//
//	explicit PlayerMovement(MoE::GameObject* const owner);
//	virtual ~PlayerMovement() = default;
//
//	virtual void SceneStart() override;
//	virtual void FixedUpdate() override;
//
//	// Getters
//	const glm::ivec2& GetHitBox() const;
//	const glm::ivec2& GetMoveDir() const;
//	const glm::vec2& GetPosition() const;
//
//	// Setters
//	void SetPosition(const glm::vec2& pos);
//
//	// Movement
//	void Move(const glm::ivec2& dir);
//	void Stop(const glm::ivec2& dir);
//	void SetPosition(const glm::ivec2& pos);
//
//private:
//
//	glm::ivec2 m_PlayerSpeed;
//	glm::ivec2 m_MovementDir;
//	glm::ivec2 m_PreviousMoveDir;
//	glm::ivec2 m_HitBoxSize;
//
//};
//
//#endif // !PLAYERMOVEMENTCOMPONENT_H
