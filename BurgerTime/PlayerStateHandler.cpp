#include "PlayerStateHandler.h"

#include "PlayerWalkState.h"
#include "PlayerAttackState.h"
#include "PlayerWinState.h"
#include "PlayerDieState.h"

#include "GameManager.h"
#include "GameObject.h"
#include "RenderComponent.h"

PlayerStateHandler::PlayerStateHandler(MoE::GameObject* const owner, Player* const player)
	: Component{ owner }
	, m_pCurrentState{ nullptr }
	, m_WalkState{ std::make_unique<PlayerWalkState>(player, this) }
	, m_AttackState{ std::make_unique<PlayerAttackState>(player, this) }
	, m_WinState{ std::make_unique<PlayerWinState>(player, this) }
	, m_DieState{ std::make_unique<PlayerDieState>(player, this) }
{
}

PlayerStateHandler::~PlayerStateHandler() = default;

void PlayerStateHandler::SceneStart()
{
	if (MoE::RenderComponent * pRenderComp{ GetOwner()->GetComponent<MoE::RenderComponent>() })
	{
		int gameScale{ GameManager::Get().GetGameScale() };
		pRenderComp->SetTextureDimensions(glm::ivec2{ 16, 16 });
		pRenderComp->ScaleTextureDimensions(static_cast<float>(gameScale));
	}
	m_pCurrentState = m_WalkState.get();
	m_pCurrentState->OnEnter();
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