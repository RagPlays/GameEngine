#ifndef PLAYERSTAEHANDLER_H
#define PLAYERSTAEHANDLER_H

#include <memory>

class PlayerIdleState;
class PlayerMoveUpState;
class PlayerMoveDownState;
class PlayerMoveLeftState;
class PlayerMoveRightState;

class Player;
class PlayerState;

class PlayerStateHandler final
{
public:

	explicit PlayerStateHandler(Player* const player);
	~PlayerStateHandler();

	PlayerStateHandler(const PlayerStateHandler& other) = delete;
	PlayerStateHandler(PlayerStateHandler&& other) noexcept = delete;
	PlayerStateHandler& operator=(const PlayerStateHandler& other) = delete;
	PlayerStateHandler& operator=(PlayerStateHandler&& other) noexcept = delete;

	void SceneStart();

	PlayerIdleState* GetIdleState() const;
	PlayerMoveUpState* GetMoveUpState() const;
	PlayerMoveDownState* GetMoveDownState() const;
	PlayerMoveLeftState* GetMoveLeftState() const;
	PlayerMoveRightState* GetMoveRightState() const;

	void SetState(PlayerState* playerState);
	void Update();

private:

	PlayerState* m_pCurrentState;

	std::unique_ptr<PlayerIdleState> m_IdleState;
	std::unique_ptr<PlayerMoveUpState> m_MoveUpState;
	std::unique_ptr<PlayerMoveDownState> m_MoveDownState;
	std::unique_ptr<PlayerMoveLeftState> m_MoveLeftState;
	std::unique_ptr<PlayerMoveRightState> m_MoveRightState;

};

#endif // !PLAYERSTAEHANDLER_H
