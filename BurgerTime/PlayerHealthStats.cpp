#include "PlayerHealthStats.h"
#include "Player.h"
#include "EventIDs.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "LevelCollision.h"
#include "LevelEnemies.h"
#include "PlayerStateHandler.h"

PlayerHealthStats::PlayerHealthStats(MoE::GameObject* const owner, Player* const playerToObserve, uint8_t playerLives)
	: Component{ owner }
	, Observer{ playerToObserve }
	, m_RemainingLives{ playerLives }
{
}

void PlayerHealthStats::OnNotify(MoE::GameObject* gameObj, EventID eventID)
{
	if (const Player* const observedPlayer{ gameObj->GetComponent<Player>() }; observedPlayer)
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
				const std::vector<Player*>& players{ LevelManager::Get().GetPlayers() };
				for (const auto& player : players)
				{
					player->Respawn();
				}
				if (LevelEnemies* enemies{ LevelManager::Get().GetEnemies() }; enemies)
				{
					enemies->Respawn();
				}
				if (PlayerStateHandler* stateHandler{ gameObj->GetComponent<PlayerStateHandler>() }; stateHandler)
				{
					stateHandler->SetWalkState();
				}
			}
		}
	}
}