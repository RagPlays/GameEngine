#ifndef LOCATOR_H
#define LOCATOR_H

#include <memory>
#include "SoundSystem.h"

class ServiceLocator final
{
public:
		
	ServiceLocator() = default;
	~ServiceLocator() = default;

	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) noexcept = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;

	// Get / Set Audio
	static SoundSystem& GetSoundSystem()
	{ 
		return *s_SoundSystemInstance;
	}
	static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
	{
		s_SoundSystemInstance = (ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss));
	}

private:

#if DEBUG || _DEBUG
	// NullAudioSytem
	// static
#else
	// AudioSystem pointer
	// static
#endif

	static std::unique_ptr<SoundSystem> s_SoundSystemInstance;

};

#endif // !LOCATOR_H
