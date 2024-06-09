#include <iostream>

#include "Enemy.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Collisions.h"
#include "EnemyStateHandler.h"
#include "Player.h"
#include "TextureRenderer.h"
#include "LevelEnemies.h"

#if defined DEBUG || defined _DEBUG
#include "Renderer.h"
#include "LevelCollision.h"
#endif

Enemy::Enemy(MoE::GameObject* const owner, EnemyType type, const glm::vec2& startPos, const glm::ivec2& startDir)
	: Component{ owner }
	, m_StartPos{ startPos }
	, m_StartDir{ startDir }
	, m_Hitbox{}
	, m_Type{ type }
	, m_pRenderComp{}
	, m_pStateHandler{}
{
	GetOwner()->SetWorldPosition(m_StartPos);
}

void Enemy::SceneStart()
{
	if (EnemyStateHandler* handler{ GetOwner()->GetComponent<EnemyStateHandler>() }; handler)
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
				static_cast<int>(renderTileSize * 0.75f),
			}
		};
		m_Hitbox = hitbox;

		m_Hitbox.pos = pos + static_cast<glm::ivec2>(static_cast<glm::vec2>(glm::ivec2{ renderTileSize, renderTileSize }) * 0.25f);
	}
	else
	{
		std::cerr << "ERROR::ENEMY::RENDERCOMPONENT_NOT_SET!\n";
		assert(false);
	}
}

void Enemy::FixedUpdate()
{
	const glm::ivec2& pos{ GetOwner()->GetWorldPosition() };
	const glm::vec2& texDim{ static_cast<glm::vec2>(m_pRenderComp->GetTextureDimentions()) };
	m_Hitbox.pos = pos + static_cast<glm::ivec2>(texDim * 0.25f);
}

#if defined DEBUG || defined _DEBUG
void Enemy::Render() const
{
	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.SetCurrentDrawColor(MoE::Color{ 255, 0, 255 });
	renderer.RenderRect(static_cast<SDL_Rect>(m_Hitbox));

	if (MoE::TextureRenderer* renderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; renderComp)
	{
		if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
		{
			const glm::ivec2& texDimentions{ renderComp->GetTextureDimentions() };
			const glm::vec2& position{ GetOwner()->GetLocalPosition() };
			const int moveOffset{ coll->GetMoveOffset() };
			const MoE::Recti moveRect
			{
				static_cast<glm::ivec2>((position + (static_cast<glm::vec2>(texDimentions) * 0.5f)) - static_cast<float>(moveOffset) * 0.5f),
				glm::ivec2{ moveOffset, moveOffset }
			};
			renderer.SetCurrentDrawColor(MoE::Color{ 0, 255, 0 });
			renderer.RenderRect(static_cast<SDL_Rect>(moveRect));
		}
	}
}
#endif

void Enemy::CheckForCollision(const MoE::Recti& burgerColl)
{
	if (m_pStateHandler && MoE::Coll::OverLapping(m_Hitbox, burgerColl))
	{
		m_pStateHandler->SetDieState();
	}
}

void Enemy::CheckForCollision(Player* player)
{
	if (m_pStateHandler && MoE::Coll::OverLapping(m_Hitbox, player->GetHitbox()))
	{
		player->Kill();
		if (LevelEnemies* enemies{ LevelManager::Get().GetEnemies() }; enemies)
		{
			enemies->GoEndState();
		}
	}
}

void Enemy::GoEndState()
{
	if (m_pStateHandler) m_pStateHandler->SetEndState();
}

void Enemy::Respawn()
{
	GetOwner()->SetWorldPosition(m_StartPos);
	m_pStateHandler->SetWalkState();
}

EnemyType Enemy::GetType() const
{
	return m_Type;
}

const glm::ivec2& Enemy::GetStartDir() const
{
	return m_StartDir;
}