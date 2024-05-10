#include "Player.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "RenderComponent.h"
#include "GameEvents.h"

unsigned int Player::s_PlayerCount{ 0 };

Player::Player(GameObject* const owner)
	: Component{ owner }
	, Subject{}
	, m_PlayerIdx{ s_PlayerCount++ }
{
	if (RenderComponent* const renderComp{ GetOwner()->GetComponent<RenderComponent>() })
	{
		const glm::ivec2& dimentions{ renderComp->GetTextureDimentions() };
		renderComp->SetTextureDimensions(dimentions * 3);
	}
}

Player::~Player()
{
	--s_PlayerCount;
}

void Player::GameStart()
{
	Notify(GetOwner(), GameEvent::playerJoined);
}

void Player::Killed()
{
	Notify(GetOwner(), GameEvent::playerDied);
	EventQueue::Get().AddEvent(GameEvent::playerDied);
}

int Player::GetPlayerIdx() const
{
	return m_PlayerIdx;
}