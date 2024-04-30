#include "SoundEventHandler.h"
#include "ResourceManager.h"
#include "SoundEffect.h"
#include "MusicPlayer.h"
#include "ServiceLocator.h"

#include "SoundIDStorage.h"

void SoundEventHandler::HandleEvent(GameEvent gameEvent)
{
	SoundSystem& soundSystem{ ServiceLocator::GetSoundSystem() };

	switch (gameEvent)
	{
	case GameEvent::gameStarts:
		soundSystem.Play(MusicSoundID::calmMusic, soundSystem.MaxVolume(), SoundType::Music);
		break;

	case GameEvent::gameEnds:
		break;

	case GameEvent::playerJoined:
		break;

	case GameEvent::playerDied:
		soundSystem.Play(SoundEffectSoundID::die, soundSystem.MaxVolume(), SoundType::SoundEffect);
		break;

	case GameEvent::foundSmallPickup:
		break;

	case GameEvent::foundLargePickup:
		break;
	}
}