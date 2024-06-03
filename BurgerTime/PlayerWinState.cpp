#include <iostream>

#include "PlayerWinState.h"
#include "PlayerStateHandler.h"
#include "LevelManager.h"
#include "Animation.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Player.h"

const int PlayerWinState::s_NrOfCycles{ 5 };

PlayerWinState::PlayerWinState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
	, m_CycleCount{}
	, m_WinAnimation{}
{
}

PlayerWinState::~PlayerWinState() = default;

void PlayerWinState::SceneStart()
{
	if (MoE::TextureRenderer* renderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() }; renderComp)
	{
		const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
		m_WinAnimation = std::make_unique<Animation>(renderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(2));
		const SDL_Rect win1Rect{ 1 * tileSize, 0 * tileSize, tileSize, tileSize };
		const SDL_Rect win2Rect{ 0 * tileSize, 4 * tileSize, tileSize, tileSize };
		m_WinAnimation->AddFrame(win1Rect);
		m_WinAnimation->AddFrame(win2Rect);
	}
}

void PlayerWinState::OnEnter()
{
	m_WinAnimation->Play();
}

void PlayerWinState::OnExit()
{
	m_WinAnimation->Stop();
}

void PlayerWinState::Update()
{
	if (m_WinAnimation)
	{
		if (m_WinAnimation->Update()) ++m_CycleCount;
		if (m_CycleCount >= s_NrOfCycles)
		{
			m_pHandler->SetWalkState();
			LevelManager::Get().NextLevel();
		}
	}
}