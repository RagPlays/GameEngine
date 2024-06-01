#include "PlayerDieState.h"
#include "Player.h"
#include "PlayerStateHandler.h"
#include "TextureRenderer.h"
#include "GameObject.h"
#include "Animation.h"

PlayerDieState::PlayerDieState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
	, m_pCurrentAnimation{}
	, m_CaughtAnimation{}
	, m_FallAnimation{}
	, m_DownAnimation{}
{
}

PlayerDieState::~PlayerDieState() = default;

void PlayerDieState::SceneStart()
{
	if (MoE::TextureRenderer* pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		InitAnimations(pRenderComp);
	}
}

void PlayerDieState::OnEnter()
{
	if (MoE::TextureRenderer* pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		pRenderComp->SetFlipMode(SDL_FLIP_NONE);
	}
	SetAnimation(m_CaughtAnimation.get());
}

void PlayerDieState::OnExit()
{
}

void PlayerDieState::Update()
{
	// Animations
	UpdateAnimations();

	// Update Other State
	UpdateStateChange();
}

// Private //

void PlayerDieState::InitAnimations(MoE::TextureRenderer* renderComp)
{
	constexpr int tileSize{ 16 };
	// Caught
	m_CaughtAnimation = std::make_unique<Animation>(renderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(4));

	const SDL_Rect caught1Rect{ 0 * tileSize, 5 * tileSize, tileSize, tileSize };
	const SDL_Rect caught2Rect{ 1 * tileSize, 5 * tileSize, tileSize, tileSize };
	m_CaughtAnimation->AddFrame(caught1Rect);
	m_CaughtAnimation->AddFrame(caught2Rect);

	// Fall
	m_FallAnimation = std::make_unique<Animation>(renderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(4));

	const SDL_Rect fall1Rect{ 2 * tileSize, 5 * tileSize, tileSize, tileSize };
	const SDL_Rect fall2Rect{ 0 * tileSize, 6 * tileSize, tileSize, tileSize };
	m_FallAnimation->AddFrame(fall1Rect);
	m_FallAnimation->AddFrame(fall2Rect);

	// Down
	m_DownAnimation = std::make_unique<Animation>(renderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(3));

	const SDL_Rect down1Rect{ 1 * tileSize, 6 * tileSize, tileSize, tileSize };
	const SDL_Rect down2Rect{ 2 * tileSize, 6 * tileSize, tileSize, tileSize };
	m_DownAnimation->AddFrame(down1Rect);
	m_DownAnimation->AddFrame(down2Rect);
}

void PlayerDieState::SetAnimation(Animation* animation)
{
	if (!animation) return;
	if (m_pCurrentAnimation) m_pCurrentAnimation->Stop();
	m_pCurrentAnimation = animation;
	m_pCurrentAnimation->Play();
}

void PlayerDieState::UpdateAnimations()
{
	if (m_pCurrentAnimation && m_pCurrentAnimation->Update())
	{
		if (m_pCurrentAnimation == m_CaughtAnimation.get())
		{
			SetAnimation(m_FallAnimation.get());
		}
		else if (m_pCurrentAnimation == m_FallAnimation.get())
		{
			SetAnimation(m_DownAnimation.get());
		}
	}
}

void PlayerDieState::UpdateStateChange()
{
	/*if (m_pPlayer->IsDead())
	{
		m_pHandler->SetDieState();
	}*/
	//if (m_pCurrentAnimation == m_DownAnimation.get())
	//{

	//}
}