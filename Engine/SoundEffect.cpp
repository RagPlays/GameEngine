#include <iostream>
#include "SoundEffect.h"

SoundEffect::SoundEffect(const std::string& filePath)
	: m_IsLoaded{ false }
	, m_FilePath{ filePath }
	, m_SoundEffect{ nullptr }
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
	m_SoundEffect = Mix_LoadWAV(m_FilePath.c_str());
	if (!m_SoundEffect)
	{
		std::cerr << "ERROR::SOUNDEFFECT::COULD_NOT_LOAD_SOUNDEFFECT_FILE: " << m_FilePath << "\n";
		return;
	}
	m_IsLoaded = true;
}

void SoundEffect::UnLoad()
{
	if (m_SoundEffect) Mix_FreeChunk(m_SoundEffect);
	m_IsLoaded = false;
}

void SoundEffect::SetVolume(int volume)
{
	Mix_VolumeChunk(m_SoundEffect, volume);
}

void SoundEffect::Play(int loops)
{
	Mix_PlayChannel(-1, m_SoundEffect, loops);
}

int SoundEffect::MaxVolume()
{
	return MIX_MAX_VOLUME;
}