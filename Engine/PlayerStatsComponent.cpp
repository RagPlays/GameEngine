#include <iostream>
#include "PlayerStatsComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextComponent.h"

PlayerStatsComponent::PlayerStatsComponent(GameObject* const owner)
	: Component{ owner }
	, Observer{}
	, m_NeedsUpdate{ true }
	, m_PlayerIdx{ -1 }
	, m_Lives{ 3 }
	, m_Score{}
{
}

void PlayerStatsComponent::Update()
{
	if (m_NeedsUpdate)
	{
		if (TextComponent* textComponent{ GetOwner()->GetComponent<TextComponent>() })
		{
			textComponent->SetText(
				"/ PLAYER: " + 
				std::to_string(m_PlayerIdx) + 
				" / Lives: " + 
				std::to_string(m_Lives) +
				" Score: " +
				std::to_string(m_Score)
				);
		}
		m_NeedsUpdate = false;
	}
}

void PlayerStatsComponent::OnNotify(GameObject* gameObj, GameEvent gameEvent)
{
	if (PlayerComponent* playerComp{ gameObj->GetComponent<PlayerComponent>() })
	{
		m_PlayerIdx = playerComp->GetPlayerIdx();

		switch (gameEvent)
		{
		case GameEvent::playerDied:
		case GameEvent::foundLargePickup:
		case GameEvent::foundSmallPickup:
			m_NeedsUpdate = true;
			break;
		default:
			break;
		}

		if (m_NeedsUpdate)
		{
			switch (gameEvent)
			{
			case GameEvent::playerDied:
				m_Lives -= 1;
				break;
			case GameEvent::foundLargePickup:
				m_Score += 100;
				break;
			case GameEvent::foundSmallPickup:
				m_Score += 10;
				break;
			}
		}
	}
}