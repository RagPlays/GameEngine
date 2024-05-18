#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <iostream>
#include <memory>

namespace MoE
{
	using SoundID = unsigned short;

	enum class SoundType
	{
		SoundEffect,
		Music
	};

	struct SoundInfo
	{
		SoundID id;
		int volume;
		SoundType type;
	};

	class SoundSystem
	{
	public:

		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		virtual void AddSong(const std::string& filePath, SoundID id) = 0;
		virtual void AddSoundEffect(const std::string& filePath, SoundID id) = 0;
		virtual void Play(SoundID id, int volume, SoundType type) = 0;

		virtual void ClearSounds() = 0;

		virtual int MaxVolume() const = 0;

	};

	class NullSoundSystem final : public SoundSystem
	{
	public:

		NullSoundSystem() = default;
		virtual ~NullSoundSystem() = default;

		virtual void AddSong(const std::string&, SoundID) override
		{
			std::cerr << "ERROR::NULLSOUNDSYSTEM::ASSIGN_FUNCTIONAL_SOUNDSYSTEM!\n";
		};
		virtual void AddSoundEffect(const std::string&, SoundID) override
		{
			std::cerr << "ERROR::NULLSOUNDSYSTEM::ASSIGN_FUNCTIONAL_SOUNDSYSTEM!\n";
		};
		virtual void Play(SoundID, int, SoundType) override {};

		virtual void ClearSounds() override {};

		virtual int MaxVolume() const override { return 0; }
	};

	class LoggingSoundSystem final : public SoundSystem
	{
	public:

		explicit LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
		{
			m_RealSS = std::move(soundSystem);
		}
		virtual ~LoggingSoundSystem() = default;

		virtual void AddSong(const std::string& filePath, SoundID id) override
		{
			std::cout << "Adding song with filename: " << filePath << " on id: " << id << ".\n";
			m_RealSS->AddSong(filePath, id);
		}

		virtual void AddSoundEffect(const std::string& filePath, SoundID id) override
		{
			std::cout << "Adding soundEffect with filename: " << filePath << " on id: " << id << ".\n";
			m_RealSS->AddSoundEffect(filePath, id);
		}

		void Play(SoundID id, int volume, SoundType type) override
		{
			m_RealSS->Play(id, volume, type);
			switch (type)
			{
			case SoundType::SoundEffect:
				std::cout << "SoundEffect ";
				break;
			case SoundType::Music:
				std::cout << "Music ";
				break;
			}
			std::cout << "played with id: " << id << " volume: " << volume << "\n";
		}

		virtual int MaxVolume() const override
		{
			return m_RealSS->MaxVolume();
		}

	private:

		std::unique_ptr<SoundSystem> m_RealSS;

	};
}

#endif // !SOUNDSYSTEM_H