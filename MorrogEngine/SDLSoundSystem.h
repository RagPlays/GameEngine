#ifndef SDLSOUNDSYSTEM_H
#define SDLSOUNDSYSTEM_H

#include <memory>

#include "SoundSystem.h"

namespace MoE
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:

		SDLSoundSystem();
		virtual ~SDLSoundSystem();

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;

		virtual void AddSong(const std::string& filePath, SoundID id) override;
		virtual void AddSoundEffect(const std::string& filePath, SoundID id) override;
		virtual void Play(SoundID id, int volume, SoundType type) override;
		virtual void ClearSounds() override;
		virtual int MaxVolume() const override;

	private:

		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_SoundSystem;

	};
}

#endif // !SDLSOUNDSYSTEM_H
