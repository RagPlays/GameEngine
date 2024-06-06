#include "PlayerAttackState.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "GameObject.h"
#include "Animation.h"
#include "LevelManager.h"
#include "Structs.h"

PlayerAttackState::PlayerAttackState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
	, m_pRenderComp{}
	, m_pCurrentAnimation{}
	, m_UpAnimation{}
	, m_DownAnimation{}
	, m_SideAnimation{}
{
}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::SceneStart()
{
	if (MoE::TextureRenderer* pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		m_pRenderComp = pRenderComp;
		InitAnimations();
	}
}

void PlayerAttackState::OnEnter()
{
	SetCorrectAnimation();
}

void PlayerAttackState::OnExit()
{
	if (m_pCurrentAnimation) m_pCurrentAnimation->Stop();
}

void PlayerAttackState::FixedUpdate()
{
}

void PlayerAttackState::Update()
{
	UpdateAnimation();
}

void PlayerAttackState::LateUpdate()
{
}

void PlayerAttackState::InitAnimations()
{
	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };

	// UP
	m_UpAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(1), static_cast<uint8_t>(2));
	const MoE::Recti up1Rect{ 2 * tileSize, 3 * tileSize, tileSize, tileSize };
	m_UpAnimation->AddFrame(up1Rect);

	// DOWN
	m_DownAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(1), static_cast<uint8_t>(2));
	const MoE::Recti down1Rect{ 0 * tileSize, 3 * tileSize, tileSize, tileSize };
	m_DownAnimation->AddFrame(down1Rect);

	// SIDE
	m_SideAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(1), static_cast<uint8_t>(2));
	const MoE::Recti side1Rect{ 1 * tileSize, 3 * tileSize, tileSize, tileSize };
	m_SideAnimation->AddFrame(side1Rect);
}

void PlayerAttackState::SetCorrectAnimation()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMoveDir() };
	if (moveDir.x)
	{
		SetAnimation(m_SideAnimation.get(), moveDir.x > 0);
	}
	else if (moveDir.y)
	{
		SetAnimation(moveDir.y > 0 ? m_DownAnimation.get() : m_UpAnimation.get());
	}
	else
	{
		SetAnimation(m_DownAnimation.get());
	}
}

void PlayerAttackState::SetAnimation(Animation* animation, bool flipped)
{
	if (!animation) return;
	if (m_pCurrentAnimation) m_pCurrentAnimation->Stop();
	m_pCurrentAnimation = animation;
	m_pCurrentAnimation->Play();

	if (flipped) m_pRenderComp->SetFlipMode(SDL_FLIP_HORIZONTAL);
	else m_pRenderComp->SetFlipMode(SDL_FLIP_NONE);
}

void PlayerAttackState::UpdateAnimation()
{
	if (m_pCurrentAnimation)
	{
		if (m_pCurrentAnimation->Update())
		{
			m_pPlayer->SetAttacking(false);
			m_pHandler->SetWalkState();
		}
	}
}