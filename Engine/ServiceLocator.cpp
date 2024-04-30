#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SDLSoundSystem.h"

std::unique_ptr<SoundSystem> ServiceLocator::s_SoundSystemInstance = std::make_unique<NullSoundSystem>();

SoundSystem& ServiceLocator::GetSoundSystem()
{
	return *s_SoundSystemInstance;
}

void ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	s_SoundSystemInstance.reset();
	s_SoundSystemInstance = (ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss));
}