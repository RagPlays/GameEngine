#include "SoundEventHandler.h"

#include "GameEvents.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SoundIDs.h"

using namespace MoE;

void SoundEventHandler::HandleEvent(GameEvent gameEvent) const
{
	SoundSystem& soundSystem{ ServiceLocator::GetSoundSystem() };
	const int maxVol{ soundSystem.MaxVolume() };

	switch (gameEvent)
	{
	case GameEvent::sceneStarts:
		soundSystem.Play(MusicSoundID::calmMusic, maxVol, SoundType::Music);
		break;

	case GameEvent::playerDied:
		soundSystem.Play(SoundEffectSoundID::die, maxVol / 10, SoundType::SoundEffect);
		break;
	}
}