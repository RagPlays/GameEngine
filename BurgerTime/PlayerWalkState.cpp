#include "PlayerWalkState.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "GameObject.h"
#include "Animation.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "Timer.h"
#include "LevelCollision.h"

PlayerWalkState::PlayerWalkState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
	, m_pRenderComp{ nullptr }
	, m_PreviousDir{}
	, m_pCurrentAnimation{ nullptr }
	, m_MovementSpeed{ 42, 22 }
{
	const int tileSize{ LevelManager::Get().GetTileSize() };
	const int gameScale{ GameManager::Get().GetGameScale() };
	m_MovementSpeed *= gameScale;
	m_HitBoxSize = glm::ivec2{ gameScale * tileSize, gameScale * tileSize };
}

PlayerWalkState::~PlayerWalkState() = default;

void PlayerWalkState::OnEnter()
{
	if (!m_pRenderComp)
	{
		if (MoE::TextureRenderer * pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
		{
			m_pRenderComp = pRenderComp;
			InitAnimations();
		}
	}
}

void PlayerWalkState::OnExit()
{
}

void PlayerWalkState::FixedUpdate()
{
	const glm::ivec2& moveDir{ m_pPlayer->GetMoveDir() };

	// Animations
	if (m_PreviousDir != moveDir)
	{
		m_PreviousDir = moveDir;
		ChangeAnimation();
	}

	// Movement
	if (!m_PreviousDir.x && !m_PreviousDir.y) return;

	if (LevelCollision * coll{ LevelManager::Get().GetCollision() })
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
			return;
		}
	}
}

void PlayerWalkState::Update()
{
	if (!m_PreviousDir.x && !m_PreviousDir.y) return;
	if (m_pCurrentAnimation) m_pCurrentAnimation->Update();
}

void PlayerWalkState::LateUpdate()
{
}

// Private //

void PlayerWalkState::InitAnimations()
{
	constexpr int tileSize{ 16 };
	// UP
	m_UpAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(3), static_cast<uint8_t>(21));
	SDL_Rect up1Rect{ 1 * tileSize, 1 * tileSize, 1 * tileSize, 1 * tileSize };
	SDL_Rect up2Rect{ 2 * tileSize, 1 * tileSize, 1 * tileSize, 1 * tileSize };
	SDL_Rect up3Rect{ 0 * tileSize, 1 * tileSize, 1 * tileSize, 1 * tileSize };
	m_UpAnimation->AddFrame(up1Rect);
	m_UpAnimation->AddFrame(up2Rect);
	m_UpAnimation->AddFrame(up3Rect);

	// DOWN
	m_DownAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(3), static_cast<uint8_t>(21));
	SDL_Rect down1Rect{ 1 * tileSize, 0 * tileSize, 1 * tileSize, 1 * tileSize };
	SDL_Rect down2Rect{ 2 * tileSize, 0 * tileSize, 1 * tileSize, 1 * tileSize };
	SDL_Rect down3Rect{ 0 * tileSize, 0 * tileSize, 1 * tileSize, 1 * tileSize };
	m_DownAnimation->AddFrame(down1Rect);
	m_DownAnimation->AddFrame(down2Rect);
	m_DownAnimation->AddFrame(down3Rect);

	// SIDEWAY
	m_SidewayAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(3), static_cast<uint8_t>(21));
	SDL_Rect side1Rect{ 1 * tileSize, 2 * tileSize, 1 * tileSize, 1 * tileSize };
	SDL_Rect side2Rect{ 2 * tileSize, 2 * tileSize, 1 * tileSize, 1 * tileSize };
	SDL_Rect side3Rect{ 0 * tileSize, 2 * tileSize, 1 * tileSize, 1 * tileSize };
	m_SidewayAnimation->AddFrame(side1Rect);
	m_SidewayAnimation->AddFrame(side2Rect);
	m_SidewayAnimation->AddFrame(side3Rect);

	m_pCurrentAnimation = m_DownAnimation.get();
}

void PlayerWalkState::ChangeAnimation()
{
	if (m_PreviousDir.x)
	{
		if (m_PreviousDir.x > 0)
		{
			// right
			SetAnimation(m_SidewayAnimation.get(), true);
		}
		else
		{
			// left
			SetAnimation(m_SidewayAnimation.get());
		}
	}
	else if (m_PreviousDir.y)
	{
		if (m_PreviousDir.y > 0)
		{
			// down
			SetAnimation(m_DownAnimation.get());
		}
		else
		{
			// up
			SetAnimation(m_UpAnimation.get());
		}
	}
}

void PlayerWalkState::SetAnimation(Animation* animation, bool flipped)
{
	if (!animation) return;

	if(m_pCurrentAnimation)
	{
		m_pCurrentAnimation->Stop();
	}
	m_pCurrentAnimation = animation;
	m_pCurrentAnimation->Play();

	if (flipped) m_pRenderComp->SetFlipMode(SDL_FLIP_HORIZONTAL);
	else m_pRenderComp->SetFlipMode(SDL_FLIP_NONE);
}