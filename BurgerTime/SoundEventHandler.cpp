#include "SoundEventHandler.h"

#include "GameEvents.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SoundIDs.h"

void SoundEventHandler::HandleEvent(GameEvent gameEvent) const
{
	SoundSystem& soundSystem{ ServiceLocator::GetSoundSystem() };
	const int maxVol{ soundSystem.MaxVolume() };

	switch (gameEvent)
	{
	case GameEvent::gameStarts:
		soundSystem.Play(MusicSoundID::calmMusic, maxVol, SoundType::Music);
		break;

	case GameEvent::playerDied:
		soundSystem.Play(SoundEffectSoundID::die, maxVol / 10, SoundType::SoundEffect);
		break;
	}
}