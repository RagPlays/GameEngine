#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <string>

struct Mix_Chunk;

namespace MoE
{
	class SoundEffect final
	{
	public:

		explicit SoundEffect(const std::string& filePath);
		~SoundEffect();

		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect(SoundEffect&& other) noexcept = delete;
		SoundEffect& operator=(const SoundEffect& other) = delete;
		SoundEffect& operator=(SoundEffect&& other) noexcept = delete;

		bool IsLoaded() const;
		void Load();
		void UnLoad();

		void SetVolume(int volume);

		void Play(int loops = 0);

		static int MaxVolume();

	private:

		bool m_IsLoaded;
		const std::string m_FilePath;
		Mix_Chunk* m_pSoundEffect;

	};
}

#endif // !SOUNDEFFECT_H
