#include "PlayerAttackState.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "GameObject.h"

PlayerAttackState::PlayerAttackState(Player* const player, PlayerStateHandler* handler)
	: PlayerState{ player, handler }
{
}

void PlayerAttackState::SceneStart()
{
	/*if (MoE::TextureRenderer * pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		InitAnimations(pRenderComp);
	}*/
}

void PlayerAttackState::OnEnter()
{
	if (MoE::TextureRenderer * pRenderComp{ m_pPlayer->GetOwner()->GetComponent<MoE::TextureRenderer>() })
	{
		pRenderComp->SetFlipMode(SDL_FLIP_NONE);
	}
}

void PlayerAttackState::OnExit()
{

}

void PlayerAttackState::FixedUpdate()
{
}

void PlayerAttackState::Update()
{

}

void PlayerAttackState::LateUpdate()
{
}
