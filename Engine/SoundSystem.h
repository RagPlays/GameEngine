#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <iostream>
#include <memory>

class SoundSystem
{
public:

	virtual ~SoundSystem() = default;
	virtual void PlaySound() = 0;

};

class NullSoundSystem final : public SoundSystem
{
public:

	virtual ~NullSoundSystem() = default;
	virtual void PlaySound() override {}

};

class LoggingSoundSystem final : public SoundSystem
{
public:

	LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
	{
		m_RealSS = std::move(soundSystem);
	}
	virtual ~LoggingSoundSystem() = default;

	virtual void PlaySound() override
	{
		m_RealSS->PlaySound();
		std::cout << "LoggingMessage for sound: " << "\n";
	}

private:

	std::unique_ptr<SoundSystem> m_RealSS;

};

#endif // !SOUNDSYSTEM_H
