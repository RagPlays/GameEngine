#include <iostream>

#include "Player.h"
#include "PlayerStateHandler.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "GameEvents.h"
#include "PlayerMovement.h"
#include "RenderComponent.h"

using namespace MoE;

unsigned int Player::s_PlayerCount{ 0 };

Player::Player(GameObject* const owner)
	: Component{ owner }
	, Subject{}
	, m_PlayerIdx{ s_PlayerCount++ }
	, m_pPlayerMovement{ nullptr }
	, m_pRenderComponent{ nullptr }
	, m_StateHandler{ this }
{
}

Player::~Player()
{
	--s_PlayerCount;
}

void Player::SceneStart()
{
	if (PlayerMovement* pMovementComp{ GetOwner()->GetComponent<PlayerMovement>() })
	{
		m_pPlayerMovement = pMovementComp;
		if (RenderComponent* const pRenderComp{ GetOwner()->GetComponent<RenderComponent>() })
		{
			m_pRenderComponent = pRenderComp;
			pRenderComp->SetTextureDimensions(pMovementComp->GetHitBox());
		}
		else assert(false);
	}
	else
	{
		std::cerr << "ERROR::PLAYER::PLAYERMOVEMENT_NOT_SET!\n";
	}

	Notify(GetOwner(), GameEvent::playerJoined);
}

void Player::Move(const glm::ivec2& dir)
{
	if (m_pPlayerMovement)
	{
		m_pPlayerMovement->Move(dir);
		UpdatePlayerState();
	}
}

void Player::Stop(const glm::ivec2& dir)
{
	if (m_pPlayerMovement)
	{
		m_pPlayerMovement->Stop(dir);
		UpdatePlayerState();
	}
}

int Player::GetPlayerIdx() const
{
	return m_PlayerIdx;
}

PlayerMovement* Player::GetMovementComponent() const
{
	return m_pPlayerMovement;
}

MoE::RenderComponent* Player::GetRenderComponent() const
{
	return m_pRenderComponent;
}

void Player::UpdatePlayerState()
{
	m_StateHandler.Update();
}