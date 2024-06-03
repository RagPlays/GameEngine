#include <iostream>

#include "PlayerStats.h"
#include "GameObject.h"
#include "Player.h"
#include "FontRenderer.h"
#include "EventIDs.h"

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
	if (!m_NeedsUpdate) return;

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

void PlayerStats::OnNotify(MoE::GameObject* gameObj, EventID eventID)
{
	if (Player* playerComp{ gameObj->GetComponent<Player>() })
	{
		switch (eventID)
		{
		case Event::sceneStarts:
			m_PlayerIdx = playerComp->GetPlayerIdx();
			break;
		case Event::playerDied:
			m_Lives -= 1;
			break;
		case Event::foundLargePickup:
			m_Score += 100;
			break;
		case Event::foundSmallPickup:
			m_Score += 10;
			break;
		default:
			return;
		}

		m_NeedsUpdate = true;
	}
}