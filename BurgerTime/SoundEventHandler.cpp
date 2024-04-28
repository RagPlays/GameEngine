#include "SoundEventHandler.h"

#include "ResourceManager.h"

#include "SoundEffect.h"
#include "MusicPlayer.h"

SoundEventHandler::SoundEventHandler()
{
	m_Music = ResourceManager::Get().LoadMusicPlayer("Sound/Music/forestMusic.mp3");
	m_DieSound = ResourceManager::Get().LoadSoundEffect("Sound/SoundEffect/dieSF.wav");
}

void SoundEventHandler::HandleEvent(GameEvent gameEvent)
{
	switch (gameEvent)
	{
	case GameEvent::gameStarts:
		m_Music->Play();
		break;

	case GameEvent::playerJoined:
		break;

	case GameEvent::playerDied:
		m_DieSound->Play();
		break;

	case GameEvent::foundSmallPickup:
		break;

	case GameEvent::foundLargePickup:
		break;
	}
}