#include "SoundEventHandler.h"

#include "EventIDs.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SoundIDs.h"

using namespace MoE;

void SoundEventHandler::HandleEvent(EventID eventID) const
{
	SoundSystem& soundSystem{ ServiceLocator::GetSoundSystem() };
	const int maxVol{ soundSystem.MaxVolume() };

	switch (eventID)
	{
	case Event::sceneStarts:
		soundSystem.Play(MusicSoundID::calmMusic, maxVol, SoundType::Music);
		break;

	case Event::playerDied:
		soundSystem.Play(SoundEffectSoundID::die, maxVol / 10, SoundType::SoundEffect);
		break;
	}
}