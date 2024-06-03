#ifndef PLAYERWINSTATE_H
#define PLAYERWINSTATE_H

#include <memory>

#include "PlayerState.h"

class Animation;

class PlayerWinState final : public PlayerState
{
public:

	explicit PlayerWinState(Player* const player, PlayerStateHandler* handler);
	virtual ~PlayerWinState();

	PlayerWinState(const PlayerWinState& other) = delete;
	PlayerWinState(PlayerWinState&& other) noexcept = delete;
	PlayerWinState& operator=(const PlayerWinState& other) = delete;
	PlayerWinState& operator=(PlayerWinState&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;

private:

	int m_CycleCount;
	static const int s_NrOfCycles;

	// Animation(s)
	std::unique_ptr<Animation> m_WinAnimation;

};

#endif // !PLAYERWINSTATE_H
