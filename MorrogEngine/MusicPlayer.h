#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <string>

struct _Mix_Music;
typedef _Mix_Music Mix_Music;

namespace MoE
{
	class MusicPlayer final
	{
	public:

		explicit MusicPlayer(const std::string& filePath);
		~MusicPlayer();

		MusicPlayer(const MusicPlayer& other) = delete;
		MusicPlayer(MusicPlayer&& other) noexcept = delete;
		MusicPlayer& operator=(const MusicPlayer& other) = delete;
		MusicPlayer& operator=(MusicPlayer&& other) noexcept = delete;

		bool IsLoaded() const;
		void Load();
		void UnLoad();

		void SetVolume(int volume);

		void Play();
		void Pause();
		void Resume();
		void Stop();

		static int MaxVolume();

	private:

		bool m_IsLoaded;
		std::string m_FilePath;
		Mix_Music* m_pMusic;

	};
}

#endif // !MUSICPLAYER_H
