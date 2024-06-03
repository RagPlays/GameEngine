#include <iostream>

#include "Player.h"
#include "PlayerStateHandler.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "EventIDs.h"
#include "TextureRenderer.h"
#include "LevelManager.h"
#include "LevelCollision.h"

#if  defined _DEBUG || defined DEBUG
#include "GameManager.h"
#include "Renderer.h"
#include "LevelCollision.h"
#endif

using namespace MoE;

unsigned int Player::s_PlayerCount{ 0 };

Player::Player(MoE::GameObject* const owner)
	: Component{ owner }
	, Subject{}
	, m_PlayerIdx{ s_PlayerCount++ }
	, m_MovementDir{}
	, m_IsDead{}
	, m_IsAttacking{}
	, m_pRenderComponent{}
{
}

Player::~Player()
{
	--s_PlayerCount;
}

void Player::SceneStart()
{
	if (MoE::TextureRenderer* pRenderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; pRenderComp)
	{
		m_pRenderComponent = pRenderComp;
		pRenderComp->SetSourceRect(16, 0, 16, 16);
	}
	if(!m_pRenderComponent)
	{
		std::cerr << "ERROR::PLAYER::RENDERCOMPONENT_NOT_SET!\n";
		assert(false);
	}
	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		GetOwner()->SetLocalPosition(coll->GetStartPos());
	}

	Notify(GetOwner(), Event::playerJoined);
}

#if  defined _DEBUG || defined DEBUG
void Player::Render() const
{
	const int tileSize{ LevelManager::Get().GetTileSize() };
	const int gameScale{ GameManager::Get().GetGameScale() };
	const glm::ivec2 hitBox{ glm::ivec2{ gameScale * tileSize, gameScale * tileSize } };
	const glm::vec2& position{ GetOwner()->GetLocalPosition() };

	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.SetCurrentDrawColor(Color{ 255, 0, 255 });
	renderer.RenderRect(Rectf{ position, static_cast<glm::vec2>(hitBox) });

	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		const int moveOffset{ coll->GetMoveOffset() };
		Recti moveRect
		{
			static_cast<glm::ivec2>((position + (static_cast<glm::vec2>(hitBox) * 0.5f)) - static_cast<float>(moveOffset) * 0.5f),
			glm::ivec2{ moveOffset, moveOffset }
		};
		renderer.SetCurrentDrawColor(Color{ 0, 255, 0 });
		renderer.RenderRect(moveRect);
	}
}
#endif

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

void Player::Kill()
{
	if (m_IsDead) return;
	m_IsDead = true;
	Notify(GetOwner(), Event::playerDied);
}

bool Player::IsDead() const
{
	return m_IsDead;
}

void Player::SetAttacking(bool attacking)
{
	m_IsAttacking = attacking;
}

bool Player::IsAttacking() const
{
	return m_IsAttacking;
}

int Player::GetPlayerIdx() const
{
	return m_PlayerIdx;
}

MoE::TextureRenderer* Player::GetRenderComponent() const
{
	return m_pRenderComponent;
}