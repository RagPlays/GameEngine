#include "PlayerHealthStats.h"
#include "Player.h"
#include "EventIDs.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "LevelCollision.h"
#include "PlayerStateHandler.h"

PlayerHealthStats::PlayerHealthStats(MoE::GameObject* const owner, Player* const playerToObserve, uint8_t playerLives)
	: Component{ owner }
	, Observer{ playerToObserve }
	, m_RemainingLives{ playerLives }
{
}

void PlayerHealthStats::OnNotify(MoE::GameObject* gameObj, EventID eventID)
{
	if (const Player* const player{ gameObj->GetComponent<Player>() }; player)
	{
		if (eventID == Event::playerDied)
		{
			if (m_RemainingLives <= 0)
			{
				// game over
				LevelManager::Get().GameOver();
			}
			else
			{
				--m_RemainingLives;
				// respawn player //
				if (LevelCollision* coll{ LevelManager::Get().GetCollision() }; coll)
				{
					gameObj->SetLocalPosition(coll->GetStartPos());
				}
				if (PlayerStateHandler* stateHandler{ gameObj->GetComponent<PlayerStateHandler>() }; stateHandler)
				{
					stateHandler->SetWalkState();
				}
				//
			}
		}
	}
}