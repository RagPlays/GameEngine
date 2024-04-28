#include <iostream>
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(const std::string& filePath)
	: m_Music{ Mix_LoadMUS(filePath.c_str()) }
{
	if (!m_Music)
	{
		std::cerr << "ERROR::MUSICPLAYER::COULD_NOT_LOAD_MUSIC_FILE\n";
	}
}

MusicPlayer::~MusicPlayer()
{
	if(m_Music) Mix_FreeMusic(m_Music);
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