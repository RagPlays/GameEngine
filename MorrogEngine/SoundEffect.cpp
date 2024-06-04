#include <iostream>

#include <SDL_mixer.h>

#include "SoundEffect.h"

namespace MoE
{
	SoundEffect::SoundEffect(const std::string& filePath)
		: m_IsLoaded{}
		, m_FilePath{ filePath }
		, m_pSoundEffect{}
	{
	}

	SoundEffect::~SoundEffect()
	{
		UnLoad();
	}

	bool SoundEffect::IsLoaded() const
	{
		return m_IsLoaded;
	}

	void SoundEffect::Load()
	{
		m_pSoundEffect = Mix_LoadWAV(m_FilePath.c_str());
		if (!m_pSoundEffect)
		{
			std::cerr << "ERROR::SOUNDEFFECT::COULD_NOT_LOAD_SOUNDEFFECT_FILE: " << m_FilePath << "\n";
			return;
		}
		m_IsLoaded = true;
	}

	void SoundEffect::UnLoad()
	{
		if (m_pSoundEffect) Mix_FreeChunk(m_pSoundEffect);
		m_IsLoaded = false;
	}

	void SoundEffect::SetVolume(int volume)
	{
		Mix_VolumeChunk(m_pSoundEffect, volume);
	}

	void SoundEffect::Play(int loops)
	{
		Mix_PlayChannel(-1, m_pSoundEffect, loops);
	}

	int SoundEffect::MaxVolume()
	{
		return MIX_MAX_VOLUME;
	}
}