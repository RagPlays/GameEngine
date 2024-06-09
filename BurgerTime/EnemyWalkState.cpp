#include "EnemyWalkState.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Animation.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "LevelCollision.h"
#include "Timer.h"
#include "EventIDs.h"
#include "EnemyStateHandler.h"

using namespace MoE;

EnemyWalkState::EnemyWalkState(Enemy* const enemy, EnemyStateHandler* handler)
	: EnemyState{ enemy, handler }
	, m_MoveDir{}
	, m_MovementSpeed{ glm::ivec2{ static_cast<int>(42 * 0.75f), static_cast<int>(22 * 0.75f) } * GameManager::Get().GetGameScale() }
	, m_CanChangeDir{}
	, m_WaitUntilDirChange{ 1.f }
	, m_CurrentDirChangeWait{}
	, m_pRenderComp{}
	, m_pCurrentAnimation{}
{
}

EnemyWalkState::~EnemyWalkState() = default;

void EnemyWalkState::SceneStart()
{
	m_MoveDir = m_pEnemy->GetStartDir();
	if (TextureRenderer* renderComp{ m_pEnemy->GetOwner()->GetComponent<TextureRenderer>() }; renderComp)
	{
		m_pRenderComp = renderComp;

		InitAnimation();

		ChangeAnimation();
	}
}

void EnemyWalkState::OnEnter()
{
	m_MoveDir = m_pEnemy->GetStartDir();
	ChangeAnimation();
}

void EnemyWalkState::OnExit()
{
	m_MoveDir = m_pEnemy->GetStartDir();
	if (m_pCurrentAnimation) m_pCurrentAnimation->Stop();
}

void EnemyWalkState::FixedUpdate()
{
	UpdateMovement();
}

void EnemyWalkState::Update()
{
	UpdateAnimation();
}

void EnemyWalkState::OnNotify(MoE::GameObject*, EventID eventID)
{
	if (eventID == Event::levelCompleted) m_pHandler->SetEndState();
}

void EnemyWalkState::InitAnimation()
{
	const int enemyType{ static_cast<int>(m_pEnemy->GetType()) };
	const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
	const int typeOffset{ tileSize * 2 * enemyType };
	// UP
	m_UpAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(12));
	const MoE::Recti up1Rect{ 4 * tileSize, 0 * tileSize + typeOffset, tileSize, tileSize };
	const MoE::Recti up2Rect{ 5 * tileSize, 0 * tileSize + typeOffset, tileSize, tileSize };
	m_UpAnimation->AddFrame(up1Rect);
	m_UpAnimation->AddFrame(up2Rect);

	// DOWN
	m_DownAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(12));
	const MoE::Recti down1Rect{ 0 * tileSize, 0 * tileSize + typeOffset, tileSize, tileSize };
	const MoE::Recti down2Rect{ 1 * tileSize, 0 * tileSize + typeOffset, tileSize, tileSize };
	m_DownAnimation->AddFrame(down1Rect);
	m_DownAnimation->AddFrame(down2Rect);

	// SIDEWAY
	m_SidewayAnimation = std::make_unique<Animation>(m_pRenderComp, static_cast<uint8_t>(2), static_cast<uint8_t>(12));
	const MoE::Recti side1Rect{ 2 * tileSize, 0 * tileSize + typeOffset, tileSize, tileSize };
	const MoE::Recti side2Rect{ 3 * tileSize, 0 * tileSize + typeOffset, tileSize, tileSize };
	m_SidewayAnimation->AddFrame(side1Rect);
	m_SidewayAnimation->AddFrame(side2Rect);
}

void EnemyWalkState::ChangeAnimation()
{
	if (m_MoveDir.x)
	{
		SetAnimation(m_SidewayAnimation.get(), m_MoveDir.x > 0);
	}
	else if (m_MoveDir.y)
	{
		SetAnimation(m_MoveDir.y > 0 ? m_DownAnimation.get() : m_UpAnimation.get());
	}
}

void EnemyWalkState::SetAnimation(Animation* animation, bool flipped)
{
	if (!animation) return;
	if (m_pCurrentAnimation) m_pCurrentAnimation->Stop();
	m_pCurrentAnimation = animation;
	m_pCurrentAnimation->Play();

	if (flipped) m_pRenderComp->SetFlipMode(SDL_FLIP_HORIZONTAL);
	else m_pRenderComp->SetFlipMode(SDL_FLIP_NONE);
}

void EnemyWalkState::UpdateMovement()
{
	if (!(m_MoveDir.x || m_MoveDir.y)) return;

	LevelCollision* coll{ LevelManager::Get().GetCollision() };
	Player* closestPlayer{ GetClosestPlayer() };
	if (!(coll && closestPlayer)) return;

	const glm::vec2& playerPos{ closestPlayer->GetOwner()->GetWorldPosition() };
	const glm::vec2& enemyPos{ m_pEnemy->GetOwner()->GetWorldPosition() };

	const glm::ivec2 diff{ playerPos - enemyPos };

	glm::ivec2 goToDir{};
	if (m_MoveDir.x)
	{
		if (std::abs(diff.y) > 0.001f)
		{
			goToDir = (diff.y > 0) ? glm::ivec2{ 0, 1 } : glm::ivec2{ 0, -1 };
		}
		else
		{
			goToDir = (diff.x > 0) ? glm::ivec2{ 1, 0 } : glm::ivec2{ -1, 0 };
		}
	}
	else
	{
		if (std::abs(diff.x) > 0.001f)
		{
			goToDir = (diff.x > 0) ? glm::ivec2{ 1, 0 } : glm::ivec2{ -1, 0 };
		}
		else
		{
			goToDir = (diff.y > 0) ? glm::ivec2{ 0, 1 } : glm::ivec2{ 0, -1 };
		}
	}

	if (!m_CanChangeDir)
	{
		m_CurrentDirChangeWait += Timer::Get().GetFixedElapsedSec();
		if (m_CurrentDirChangeWait >= m_WaitUntilDirChange) m_CanChangeDir = true;
	}

	if (!TryMove(goToDir, coll))
	{
		if (goToDir.x) goToDir = (diff.y > 0) ? glm::ivec2{ 0, 1 } : glm::ivec2{ 0, -1 };
		else goToDir = (diff.x > 0) ? glm::ivec2{ 1, 0 } : glm::ivec2{ -1, 0 };

		if (!TryMove(goToDir, coll))
		{
			const glm::ivec2 perpendicularDir1{ m_MoveDir.y, -m_MoveDir.x };
			const glm::ivec2 perpendicularDir2{ -m_MoveDir.y, m_MoveDir.x };

			if (!TryMove(perpendicularDir1, coll)) TryMove(perpendicularDir2, coll);
		}
	}
}

bool EnemyWalkState::TryMove(const glm::ivec2& dir, LevelCollision* coll)
{
	bool hasMoved{ true };
	const glm::vec2 previousPos{ m_pEnemy->GetOwner()->GetWorldPosition() };
	const float fixedTime{ MoE::Timer::Get().GetFixedElapsedSec() };
	const glm::vec2 moveScale{ static_cast<glm::vec2>(m_MovementSpeed) * fixedTime };
	const glm::ivec2& moveHitbox{ m_pRenderComp->GetTextureDimentions() };
	const glm::vec2 translation{ static_cast<glm::vec2>(m_MoveDir) * moveScale };

	m_pEnemy->GetOwner()->Translate(translation);
	const MoveResult moveResult{ coll->CanMove(previousPos, m_MoveDir, moveHitbox, false) };
	if (!moveResult.canMove)
	{
		hasMoved = false;
		m_pEnemy->GetOwner()->SetWorldPosition(previousPos);
	}
	else
	{
		const glm::vec2& pos{ m_pEnemy->GetOwner()->GetWorldPosition() };
		glm::vec newPos{ pos };
		if (m_MoveDir.x) newPos.y = moveResult.line.pointOne.y - (moveHitbox.y * 0.5f);
		else newPos.x = moveResult.line.pointOne.x - (moveHitbox.x * 0.5f);
		m_pEnemy->GetOwner()->SetWorldPosition(newPos);
	}

	if ((m_MoveDir.x > 0 && dir.x < 0) ||
		(m_MoveDir.x < 0 && dir.x > 0) ||
		(m_MoveDir.y > 0 && dir.y < 0) ||
		(m_MoveDir.y < 0 && dir.y > 0)) return hasMoved;

	if (m_CanChangeDir)
	{
		const glm::vec2& freshPos{ m_pEnemy->GetOwner()->GetWorldPosition() };

		const MoveResult wantMoveResults{ coll->CanMove(freshPos, dir, moveHitbox, false) };
		if (wantMoveResults.canMove)
		{
			m_MoveDir = dir;
			m_CanChangeDir = false;
			m_CurrentDirChangeWait = 0.f;
			ChangeAnimation();
		}
	}

	return hasMoved;
}

void EnemyWalkState::UpdateAnimation()
{
	if (m_pCurrentAnimation) m_pCurrentAnimation->Update();
}

Player* EnemyWalkState::GetClosestPlayer() const
{
	const glm::vec2& enemyPos{ m_pEnemy->GetOwner()->GetWorldPosition() };
	const std::vector<Player*>& players{ LevelManager::Get().GetPlayers() };

	if (players.empty()) return nullptr;

	Player* closestPlayer{};
	float minDistance{ std::numeric_limits<float>::max() };

	for (const auto& player : players)
	{
		const glm::vec2& playerPos{ player->GetOwner()->GetWorldPosition() };
		float distance{ glm::distance(enemyPos, playerPos) };

		if (distance < minDistance)
		{
			minDistance = distance;
			closestPlayer = player;
		}
	}

	return closestPlayer;
}