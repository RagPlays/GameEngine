#include "PlayerStateHandler.h"

#include "PlayerWalkState.h"
#include "PlayerAttackState.h"
#include "PlayerWinState.h"
#include "PlayerDieState.h"

#include "GameManager.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "LevelManager.h"
#include "LevelCollision.h"

PlayerStateHandler::PlayerStateHandler(MoE::GameObject* const owner, Player* const player)
	: Component{ owner }
	, Observer{ &LevelManager::Get() }
	, m_pPlayer{ player }
	, m_pCurrentState{}
	, m_WalkState{ std::make_unique<PlayerWalkState>(player, this) }
	, m_AttackState{ std::make_unique<PlayerAttackState>(player, this) }
	, m_WinState{ std::make_unique<PlayerWinState>(player, this) }
	, m_DieState{ std::make_unique<PlayerDieState>(player, this) }
{
}

PlayerStateHandler::~PlayerStateHandler() = default;

void PlayerStateHandler::SceneStart()
{
	if (MoE::TextureRenderer* pRenderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		const int gameScale{ GameManager::Get().GetGameScale() };
		pRenderComp->SetTextureDimensions(glm::ivec2{ 16, 16 });
		pRenderComp->ScaleTextureDimensions(static_cast<float>(gameScale));
	}

	if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
	{
		GetOwner()->SetLocalPosition(coll->GetStartPos());
	}

	if(m_WalkState) m_WalkState->SceneStart();
	if (m_AttackState) m_AttackState->SceneStart();
	if (m_WinState) m_WinState->SceneStart();
	if (m_DieState) m_DieState->SceneStart();

	m_pCurrentState = m_WalkState.get();
	if(m_pCurrentState) m_pCurrentState->OnEnter();
}

void PlayerStateHandler::FixedUpdate()
{
	if (m_pCurrentState) m_pCurrentState->FixedUpdate();
}

void PlayerStateHandler::Update()
{
	if(m_pCurrentState) m_pCurrentState->Update();
}

void PlayerStateHandler::LateUpdate()
{
	if (m_pCurrentState) m_pCurrentState->LateUpdate();
}

void PlayerStateHandler::OnNotify(MoE::GameObject* gameObj, EventID eventID)
{
	if (m_pCurrentState) m_pCurrentState->OnNotify(gameObj, eventID);
}

void PlayerStateHandler::Notify(EventID eventID)
{
	m_pPlayer->Notify(m_pPlayer->GetOwner(), eventID);
}

void PlayerStateHandler::SetState(PlayerState* playerState)
{
	if (!playerState || m_pCurrentState == playerState) return;
	if (m_pCurrentState)
	{
		m_pCurrentState->OnExit();
	}
	m_pCurrentState = playerState;
	m_pCurrentState->OnEnter();
}

void PlayerStateHandler::SetWalkState()
{
	SetState(m_WalkState.get());
}

void PlayerStateHandler::SetAttackState()
{
	SetState(m_AttackState.get());
}

void PlayerStateHandler::SetWinState()
{
	SetState(m_WinState.get());
}

void PlayerStateHandler::SetDieState()
{
	SetState(m_DieState.get());
}