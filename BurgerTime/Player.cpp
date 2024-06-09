#include <iostream>

#include "Player.h"
#include "PlayerStateHandler.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "EventIDs.h"
#include "TextureRenderer.h"
#include "LevelManager.h"
#include "LevelCollision.h"
#include "GameManager.h"
#include "LevelEnemies.h"
#include "Timer.h"

#if  defined _DEBUG || defined DEBUG
#include "Renderer.h"
#endif

using namespace MoE;

unsigned int Player::s_PlayerCount{ 0 };

Player::Player(MoE::GameObject* const owner)
	: Component{ owner }
	, Subject{}
	, m_PlayerIdx{ s_PlayerCount++ }
	, m_RespawnProtectTime{ 2.f }
	, m_CurrentProtectTime{}
	, m_MovementDir{}
	, m_Hitbox{}
	, m_pRenderComp{}
	, m_pStateHandler{}
{
	LevelManager::Get().RegisterPlayer(this);
}

Player::~Player()
{
	LevelManager::Get().UnRegisterPlayer(this);
	--s_PlayerCount;
}

void Player::SceneStart()
{
	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		GetOwner()->SetWorldPosition(coll->GetStartPos());
	}

	if (PlayerStateHandler* handler{ GetOwner()->GetComponent<PlayerStateHandler>() }; handler)
	{
		m_pStateHandler = handler;
	}
	else
	{
		std::cerr << "ERROR::PLAYER::PLAYERSTATEHANDLER_NOT_SET!\n";
		assert(false);
	}

	if (MoE::TextureRenderer* pRenderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; pRenderComp)
	{
		m_pRenderComp = pRenderComp;
		const int gameScale{ GameManager::Get().GetGameScale() };
		const int tileSize{ static_cast<int>(LevelManager::Get().GetTileSize()) };
		const int renderTileSize{ tileSize * gameScale };
		pRenderComp->SetTextureDimensions(glm::ivec2{ tileSize, tileSize });
		pRenderComp->ScaleTextureDimensions(static_cast<float>(gameScale));
		const glm::ivec2& pos{ static_cast<glm::ivec2>(GetOwner()->GetWorldPosition()) };
		
		const MoE::Recti hitbox
		{
			pos,
			glm::ivec2
			{
				static_cast<int>(renderTileSize * 0.5f),
				static_cast<int>(renderTileSize * 0.65f),
			}
		};
		m_Hitbox = hitbox;

		m_Hitbox.pos.x = pos.x + static_cast<int>(renderTileSize * 0.25f);
		m_Hitbox.pos.y = pos.y + static_cast<int>(renderTileSize * 0.35f);
	}
	else
	{
		std::cerr << "ERROR::PLAYER::RENDERCOMPONENT_NOT_SET!\n";
		assert(false);
	}

	Notify(GetOwner(), Event::playerJoined);
}

void Player::FixedUpdate()
{
	const glm::ivec2& pos{ GetOwner()->GetWorldPosition() };
	const glm::vec2& texDim{ static_cast<glm::vec2>(m_pRenderComp->GetTextureDimentions()) };
	m_Hitbox.pos.x = pos.x + static_cast<int>(texDim.x * 0.25f);
	m_Hitbox.pos.y = pos.y + static_cast<int>(texDim.y * 0.35f);
}

#if  defined _DEBUG || defined DEBUG
void Player::Render() const
{
	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.SetCurrentDrawColor(Color{ 255, 0, 255 });
	renderer.RenderRect(static_cast<SDL_Rect>(m_Hitbox));

	if (MoE::TextureRenderer* renderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; renderComp)
	{
		if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
		{
			const glm::ivec2& texDimentions{ renderComp->GetTextureDimentions() };
			const glm::vec2& position{ GetOwner()->GetLocalPosition() };
			const int moveOffset{ coll->GetMoveOffset() };
			const Recti moveRect
			{
				static_cast<glm::ivec2>((position + (static_cast<glm::vec2>(texDimentions) * 0.5f)) - static_cast<float>(moveOffset) * 0.5f),
				glm::ivec2{ moveOffset, moveOffset }
			};
			renderer.SetCurrentDrawColor(Color{ 0, 255, 0 });
			renderer.RenderRect(static_cast<SDL_Rect>(moveRect));
		}
	}
}
#endif

void Player::LateUpdate()
{
	if (m_CurrentProtectTime >= m_RespawnProtectTime)
	{
		if (LevelEnemies* enemies{ LevelManager::Get().GetEnemies() }; enemies)
		{
			enemies->CheckForCollision(this);
		}
	}
	else m_CurrentProtectTime += MoE::Timer::Get().GetFixedElapsedSec();
}

void Player::Move(const glm::ivec2& dir)
{
	m_MovementDir = dir;
}

void Player::Stop(const glm::ivec2& dir)
{
	if (dir.y * m_MovementDir.y > 0)
	{
		m_MovementDir.y = 0;
	}
	else if (dir.x * m_MovementDir.x > 0)
	{
		m_MovementDir.x = 0;
	}
}

const glm::ivec2& Player::GetMoveDir() const
{
	return m_MovementDir;
}

const MoE::Recti& Player::GetHitbox() const
{
	return m_Hitbox;
}

void Player::Kill()
{
	GetOwner()->GetComponent<PlayerStateHandler>()->SetDieState();
}

void Player::Attack()
{
	if (m_pStateHandler) m_pStateHandler->SetAttackState();
}

void Player::Respawn()
{
	m_CurrentProtectTime = 0.f;
	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		GetOwner()->SetWorldPosition(coll->GetStartPos());
	}
}

int Player::GetPlayerIdx() const
{
	return m_PlayerIdx;
}