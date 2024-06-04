#include "PlayerWalkState.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "GameObject.h"
#include "Animation.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "Timer.h"
#include "LevelCollision.h"
#include "EventIDs.h"

PlayerWalkState::PlayerWalkState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
	, m_pRenderComp{}
	, m_MovementSpeed{ glm::ivec2{42, 22} * GameManager::Get().GetGameScale() }
	, m_PreviousDir{}
	, m_HitBoxSize
	{ 
		GameManager::Get().GetGameScale() * LevelManager::Get().GetTileSize(),
		GameManager::Get().GetGameScale()* LevelManager::Get().GetTileSize()
	}
	, m_pCurrentAnimation{}
	, m_UpAnimation{}
	, m_DownAnimation{}
	, m_SidewayAnimation{}
{
}

PlayerWalkState::~PlayerWalkState() = default;

void PlayerWalkState::SceneStart()
{
	if (MoE::TextureRenderer * pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		m_pRenderComp = pRenderComp;
		InitAnimations();
	}
}

void PlayerWalkState::OnEnter()
{
	SetAnimation(m_DownAnimation.get());
	ChangeAnimation();
}

void PlayerWalkState::OnExit()
{
	if (m_pCurrentAnimation) m_pCurrentAnimation->Stop();
}

void PlayerWalkState::FixedUpdate()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMoveDir() };

	// Animations
	if (m_PreviousDir != moveDir)
	{
		ChangeAnimation();
		m_PreviousDir = moveDir;
	}

	// Movement
	UpdateMovement();
}

void PlayerWalkState::Update()
{
	// Animations
	UpdateAnimation();

	// Update Other State
	UpdateStateChange();
}

void PlayerWalkState::OnNotify(MoE::GameObject*, EventID eventID)
{
	if (eventID == Event::levelCompleted) m_pHandler->SetWinState();
}

// Private //

void PlayerWalkState::InitAnimations()
{
	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
	// UP
	m_UpAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(3), static_cast<uint8_t>(21));
	SDL_Rect up1Rect{ 1 * tileSize, 1 * tileSize, tileSize, tileSize };
	SDL_Rect up2Rect{ 2 * tileSize, 1 * tileSize, tileSize, tileSize };
	SDL_Rect up3Rect{ 0 * tileSize, 1 * tileSize, tileSize, tileSize };
	m_UpAnimation->AddFrame(up1Rect);
	m_UpAnimation->AddFrame(up2Rect);
	m_UpAnimation->AddFrame(up3Rect);

	// DOWN
	m_DownAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(3), static_cast<uint8_t>(21));
	SDL_Rect down1Rect{ 1 * tileSize, 0 * tileSize, tileSize, tileSize };
	SDL_Rect down2Rect{ 2 * tileSize, 0 * tileSize, tileSize, tileSize };
	SDL_Rect down3Rect{ 0 * tileSize, 0 * tileSize, tileSize, tileSize };
	m_DownAnimation->AddFrame(down1Rect);
	m_DownAnimation->AddFrame(down2Rect);
	m_DownAnimation->AddFrame(down3Rect);

	// SIDEWAY
	m_SidewayAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(3), static_cast<uint8_t>(21));
	SDL_Rect side1Rect{ 1 * tileSize, 2 * tileSize, tileSize, tileSize };
	SDL_Rect side2Rect{ 2 * tileSize, 2 * tileSize, tileSize, tileSize };
	SDL_Rect side3Rect{ 0 * tileSize, 2 * tileSize, tileSize, tileSize };
	m_SidewayAnimation->AddFrame(side1Rect);
	m_SidewayAnimation->AddFrame(side2Rect);
	m_SidewayAnimation->AddFrame(side3Rect);
}

void PlayerWalkState::ChangeAnimation()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMoveDir() };
	if (moveDir.x)
	{
		SetAnimation(m_SidewayAnimation.get(), moveDir.x > 0);
	}
	else if (moveDir.y)
	{
		SetAnimation(moveDir.y > 0 ? m_DownAnimation.get() : m_UpAnimation.get());
	}
	else if (m_PreviousDir.x || m_PreviousDir.y)
	{
		SetAnimation(m_PreviousDir.y < 0 ? m_UpAnimation.get() : m_DownAnimation.get());
	}
}

void PlayerWalkState::SetAnimation(Animation* animation, bool flipped)
{
	if (!animation) return;
	if(m_pCurrentAnimation) m_pCurrentAnimation->Stop();
	m_pCurrentAnimation = animation;
	m_pCurrentAnimation->Play();

	if (flipped) m_pRenderComp->SetFlipMode(SDL_FLIP_HORIZONTAL);
	else m_pRenderComp->SetFlipMode(SDL_FLIP_NONE);
}

void PlayerWalkState::UpdateMovement()
{
	if (!m_PreviousDir.x && !m_PreviousDir.y) return;

	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		MoE::GameObject* owner{ m_pPlayer->GetOwner() };
		const float fixedTime{ MoE::Timer::Get().GetFixedElapsedSec() };
		const glm::vec2 moveScale{ static_cast<glm::vec2>(m_MovementSpeed) * fixedTime };
		const glm::vec2 translation{ static_cast<glm::vec2>(m_PreviousDir) * moveScale };
		const glm::vec2 originalPos{ owner->GetLocalPosition() };

		owner->Translate(translation);

		if (!coll->CanMove(m_pPlayer, m_HitBoxSize))
		{
			owner->SetLocalPosition(originalPos);
			if (m_pCurrentAnimation)
			{
				m_pCurrentAnimation->Stop();
			}
		}
	}
}

void PlayerWalkState::UpdateAnimation()
{
	if (!m_PreviousDir.x && !m_PreviousDir.y) return;
	if (m_pCurrentAnimation) m_pCurrentAnimation->Update();
}

void PlayerWalkState::UpdateStateChange()
{
	if (m_pPlayer->IsAttacking())
	{
		m_pHandler->SetAttackState();
	}
}