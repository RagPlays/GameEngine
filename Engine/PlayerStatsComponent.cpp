#include "PlayerStatsComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextComponent.h"

PlayerStatsComponent::PlayerStatsComponent(GameObject* const owner, PlayerComponent* const observedPlayer)
	: Component{ owner }
	, Observer{}
	, m_ObservedPlayer{ observedPlayer }
	, m_NeedsUpdate{ true }
{
	if (m_ObservedPlayer) m_ObservedPlayer->RegisterObserver(this);
}

void PlayerStatsComponent::Update()
{
	if (m_NeedsUpdate)
	{
		if (TextComponent* textComponent{ GetOwner()->GetComponent<TextComponent>() })
		{
			textComponent->SetText(
				"/ PLAYER: " + 
				std::to_string(m_ObservedPlayer->GetPlayerIdx()) + 
				" / Lives: " + 
				std::to_string(m_ObservedPlayer->GetLives()) +
				" Score: " +
				std::to_string(m_ObservedPlayer->GetScore())
				);
		}

		m_NeedsUpdate = false;
	}
}

void PlayerStatsComponent::OnNotify(GameObject*, GameEvent gameEvent)
{
	switch (gameEvent)
	{
	case GameEvent::playerDied:
	case GameEvent::foundPickup:
		m_NeedsUpdate = true;
		break;
	default:
		break;
	}
}