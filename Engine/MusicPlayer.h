#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class MusicPlayer final
{
public:

	explicit MusicPlayer(const std::string& filePath);
	~MusicPlayer();

	MusicPlayer(const MusicPlayer& other) = delete;
	MusicPlayer(MusicPlayer&& other) noexcept = delete;
	MusicPlayer& operator=(const MusicPlayer& other) = delete;
	MusicPlayer& operator=(MusicPlayer&& other) noexcept = delete;

	void Play();
	void Pause();
	void Resume();
	void Stop();

private:

	Mix_Music* m_Music;

};

#endif // !MUSICPLAYER_H
