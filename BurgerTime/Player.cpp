#include <iostream>

#include "Player.h"
#include "PlayerStateHandler.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "GameEvents.h"
#include "PlayerMovement.h"
#include "TextureRenderer.h"
#include "LevelManager.h"
#include "LevelCollision.h"

unsigned int Player::s_PlayerCount{ 0 };

Player::Player(MoE::GameObject* const owner)
	: Component{ owner }
	, Subject{}
	, m_PlayerIdx{ s_PlayerCount++ }
	, m_MovementDir{}
	, m_pRenderComponent{ nullptr }
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

	Notify(GetOwner(), MoE::GameEvent::playerJoined);
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

int Player::GetPlayerIdx() const
{
	return m_PlayerIdx;
}

MoE::TextureRenderer* Player::GetRenderComponent() const
{
	return m_pRenderComponent;
}