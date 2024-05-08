#include "PlayerComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "EventQueue.h"
#include "RenderComponent.h"

unsigned int PlayerComponent::s_PlayerCount{ 0 };

PlayerComponent::PlayerComponent(GameObject* const owner)
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

PlayerComponent::~PlayerComponent()
{
	--s_PlayerCount;
}

void PlayerComponent::GameStart()
{
	Notify(GetOwner(), GameEvent::playerJoined);
}

void PlayerComponent::Killed()
{
	Notify(GetOwner(), GameEvent::playerDied);
	EventQueue::Get().AddEvent(GameEvent::playerDied);
}

int PlayerComponent::GetPlayerIdx() const
{
	return m_PlayerIdx;
}