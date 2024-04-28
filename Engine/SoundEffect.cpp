#include <iostream>
#include "SoundEffect.h"

SoundEffect::SoundEffect(const std::string& filePath)
	: m_SoundEffect{ Mix_LoadWAV(filePath.c_str()) }
{
	if (!m_SoundEffect)
	{
		std::cerr << "ERROR::SOUNDEFFECT::COULD_NOT_LOAD_SOUNDEFFECT_FILE\n";
	}
}

SoundEffect::~SoundEffect()
{
	if(m_SoundEffect) Mix_FreeChunk(m_SoundEffect);
}

void SoundEffect::Play()
{
	Mix_PlayChannel(-1, m_SoundEffect, 0);
}

void SoundEffect::Play(int loops)
{
	Mix_PlayChannel(-1, m_SoundEffect, loops);
}