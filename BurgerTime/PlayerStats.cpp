#include <iostream>

#include "PlayerStats.h"
#include "GameObject.h"
#include "Player.h"
#include "FontRenderer.h"
#include "GameEvents.h"

using namespace MoE;

PlayerStats::PlayerStats(GameObject* const owner, Subject* const subject)
	: Component{ owner }
	, Observer{ subject }
	, m_NeedsUpdate{ true }
	, m_PlayerIdx{ -1 }
	, m_Lives{ 3 }
	, m_Score{}
{
}

void PlayerStats::Update()
{
	if (m_NeedsUpdate)
	{
		if (FontRenderer * fontRenderer{ GetOwner()->GetComponent<FontRenderer>() })
		{
			fontRenderer->SetText(
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

void PlayerStats::OnNotify(GameObject* gameObj, GameEvent gameEvent)
{
	if (Player* playerComp{ gameObj->GetComponent<Player>() })
	{
		switch (gameEvent)
		{
		case GameEvent::sceneStarts:
			m_PlayerIdx = playerComp->GetPlayerIdx();
			break;
		case GameEvent::playerDied:
			m_Lives -= 1;
			break;
		case GameEvent::foundLargePickup:
			m_Score += 100;
			break;
		case GameEvent::foundSmallPickup:
			m_Score += 10;
			break;
		default:
			return;
		}

		m_NeedsUpdate = true;
	}
}