#include <iostream>

#include <SDL_mixer.h>

#include "MusicPlayer.h"

namespace MoE
{
	MusicPlayer::MusicPlayer(const std::string& filePath)
		: m_IsLoaded{ }
		, m_FilePath{ filePath }
		, m_pMusic{}
	{
	}

	MusicPlayer::~MusicPlayer()
	{
		UnLoad();
	}

	void MusicPlayer::Load()
	{
		m_pMusic = Mix_LoadMUS(m_FilePath.c_str());
		if (!m_pMusic)
		{
			std::cerr << "ERROR::MUSICPLAYER::COULD_NOT_LOAD_MUSIC_FILE: " << m_FilePath << "\n";
			return;
		}
		m_IsLoaded = true;
	}

	void MusicPlayer::UnLoad()
	{
		if (m_pMusic) Mix_FreeMusic(m_pMusic);
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
		Mix_PlayMusic(m_pMusic, -1);
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
}