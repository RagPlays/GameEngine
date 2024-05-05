#include <iostream>
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(const std::string& filePath)
	: m_IsLoaded{ false }
	, m_FilePath{ filePath }
	, m_Music{ nullptr }
{
}

MusicPlayer::~MusicPlayer()
{
	UnLoad();
}

void MusicPlayer::Load()
{
	m_Music = Mix_LoadMUS(m_FilePath.c_str());
	if (!m_Music)
	{
		std::cerr << "ERROR::MUSICPLAYER::COULD_NOT_LOAD_MUSIC_FILE: " << m_FilePath << "\n";
		return;
	}
	m_IsLoaded = true;
}

void MusicPlayer::UnLoad()
{
	if (m_Music) Mix_FreeMusic(m_Music);
	m_IsLoaded = false;
}

bool MusicPlayer::IsLoaded() const
{
	return m_IsLoaded;
}

void MusicPlayer::SetVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void MusicPlayer::Play()
{
	Mix_PlayMusic(m_Music, -1);
}

void MusicPlayer::Pause()
{
	Mix_PauseMusic();
}

void MusicPlayer::Resume()
{
	Mix_ResumeMusic();
}

void MusicPlayer::Stop()
{
	Mix_HaltMusic();
}

int MusicPlayer::MaxVolume()
{
	return MIX_MAX_VOLUME;
}