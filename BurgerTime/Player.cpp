#include <iostream>

#include "Player.h"
#include "PlayerStateHandler.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "EventIDs.h"
#include "TextureRenderer.h"
#include "LevelManager.h"

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
	, m_HitBox{}
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

		m_HitBox.size.x = static_cast<int>(0.5f * m_pRenderComponent->GetTextureWidth());
		m_HitBox.size.y = static_cast<int>(m_pRenderComponent->GetTextureHeight() * 0.75f);
		const glm::ivec2& pos{ GetOwner()->GetLocalPosition() };

		m_HitBox.pos.x = pos.x + static_cast<int>(m_pRenderComponent->GetTextureWidth() * 0.25f);
		m_HitBox.pos.y = pos.y;
	}
	if(!m_pRenderComponent)
	{
		std::cerr << "ERROR::PLAYER::RENDERCOMPONENT_NOT_SET!\n";
		assert(false);
	}

	Notify(GetOwner(), Event::playerJoined);
}

void Player::FixedUpdate()
{
	if (m_pRenderComponent)
	{
		const glm::ivec2& pos{ GetOwner()->GetLocalPosition() };

		m_HitBox.pos.x = pos.x + static_cast<int>(m_pRenderComponent->GetTextureWidth() * 0.25);
		m_HitBox.pos.y = pos.y + static_cast<int>(m_pRenderComponent->GetTextureHeight() * 0.25);
	}
}

#if  defined _DEBUG || defined DEBUG
void Player::Render() const
{
	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.SetCurrentDrawColor(Color{ 255, 0, 255 });
	renderer.RenderRect(static_cast<SDL_Rect>(m_HitBox));

	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		const glm::ivec2& texDimentions{ m_pRenderComponent->GetTextureDimentions() };
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

const MoE::Recti& Player::GetHitbox() const
{
	return m_HitBox;
}

void Player::Kill()
{
	GetOwner()->GetComponent<PlayerStateHandler>()->SetDieState(); // debug code needs to be fixed!!
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