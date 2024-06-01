#include "SDLSoundSystem.h"

#include <unordered_map>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "SoundEffect.h"
#include "MusicPlayer.h"

#include "ResourceManager.h"

namespace MoE
{
	// SOUNDSYSTEMIMPL //
	class SDLSoundSystem::SDLSoundSystemImpl final : public SoundSystem
	{
	public:

		SDLSoundSystemImpl();
		virtual ~SDLSoundSystemImpl();

		SDLSoundSystemImpl(const SDLSoundSystemImpl& other) = delete;
		SDLSoundSystemImpl(SDLSoundSystemImpl&& other) noexcept = delete;
		SDLSoundSystemImpl& operator=(const SDLSoundSystemImpl& other) = delete;
		SDLSoundSystemImpl& operator=(SDLSoundSystemImpl&& other) noexcept = delete;

		virtual void AddSong(const std::string& filePath, SoundID id) override;
		virtual void AddSoundEffect(const std::string& filePath, SoundID id) override;
		virtual void Play(const SoundID id, int volume, SoundType type) override;

		virtual void ClearSounds() override;
		
		virtual int MaxVolume() const override;

	private:

		void HandleEvents();

	private:

		std::unordered_map<SoundID, std::unique_ptr<SoundEffect>> m_SoundEffects;
		std::unordered_map<SoundID, std::unique_ptr<MusicPlayer>> m_Music;

		std::queue<SoundInfo> m_Queue;

		bool m_SoundThreadRunning;
		std::condition_variable m_ConditionToRun;
		std::mutex m_Mutex;
		std::jthread m_SoundThread;

	};

	SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
		: m_SoundEffects{}
		, m_Music{}
		, m_Queue{}
		, m_SoundThreadRunning{ true }
		, m_ConditionToRun{}
		, m_Mutex{}
		, m_SoundThread{ std::jthread{[this] { this->HandleEvents(); }} }
	{
		m_SoundEffects.clear();
		m_Music.clear();
	}

	SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
	{
		m_SoundThreadRunning = false;
		m_ConditionToRun.notify_one();
		if (m_SoundThread.joinable())
		{
			m_SoundThread.join();
		}

		m_SoundEffects.clear();
		m_Music.clear();
	}

	void SDLSoundSystem::SDLSoundSystemImpl::AddSong(const std::string& filePath, SoundID id)
	{
		const std::string fullPath{ ResourceManager::Get().GetFullPath(filePath) };

		std::unique_lock<std::mutex> lock(m_Mutex);

		if (m_Music.find(id) != m_Music.end())
		{
			std::cerr << "ERROR::SDLSOUNDSYSTEMIMPL::SOUNDID_" << id << "_IS_ALREADY_IN_MUSIC\n";
			return;
		}
		m_Music[id] = std::make_unique<MusicPlayer>(fullPath);
	}

	void SDLSoundSystem::SDLSoundSystemImpl::AddSoundEffect(const std::string& filePath, SoundID id)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		if (m_SoundEffects.find(id) != m_SoundEffects.end())
		{
			std::cerr << "ERROR::SDLSOUNDSYSTEMIMPL::SOUNDID_" << id << "_IS_ALREADY_IN_SOUNDEFFECTS\n";
			return;
		}
		m_SoundEffects[id] = std::make_unique<SoundEffect>(ResourceManager::Get().GetFullPath(filePath));
	}

	void SDLSoundSystem::SDLSoundSystemImpl::Play(SoundID id, int volume, SoundType type)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		m_Queue.push(SoundInfo{ id, volume, type });
		m_ConditionToRun.notify_one();
	}

	void SDLSoundSystem::SDLSoundSystemImpl::ClearSounds()
	{
		m_SoundEffects.clear();
		m_Music.clear();
	}

	int SDLSoundSystem::SDLSoundSystemImpl::MaxVolume() const
	{
		return SoundEffect::MaxVolume();
	}

	void SDLSoundSystem::SDLSoundSystemImpl::HandleEvents()
	{
		while (m_SoundThreadRunning)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);

			m_ConditionToRun.wait(lock,
				[&]()
				{
					return !(m_Queue.empty() && m_SoundThreadRunning);
				}
			);
			if (!m_SoundThreadRunning) break;

			SoundInfo soundInfo{ m_Queue.front() };
			m_Queue.pop();

			lock.unlock();

			SoundID id{ soundInfo.id };
			int volume{ soundInfo.volume };

			switch (soundInfo.type)
			{
			case SoundType::SoundEffect:
				if (!m_SoundEffects[id]->IsLoaded())
				{
					m_SoundEffects[id]->Load();
				}
				m_SoundEffects[id]->SetVolume(volume);
				m_SoundEffects[id]->Play();
				break;
			case SoundType::Music:
				if (!m_Music[id]->IsLoaded())
				{
					m_Music[id]->Load();
				}
				m_Music[id]->SetVolume(volume);
				m_Music[id]->Play();
				break;
			}
		}
	}

	// SOUNDSYSTEM //
	SDLSoundSystem::SDLSoundSystem()
		: m_SoundSystem{ std::make_unique<SDLSoundSystemImpl>() }
	{
	}

	SDLSoundSystem::~SDLSoundSystem() = default;

	void SDLSoundSystem::AddSong(const std::string& filePath, SoundID id)
	{
		m_SoundSystem->AddSong(filePath, id);
	}

	void SDLSoundSystem::AddSoundEffect(const std::string& filePath, SoundID id)
	{
		m_SoundSystem->AddSoundEffect(filePath, id);
	}

	void SDLSoundSystem::Play(SoundID id, int volume, SoundType type)
	{
		m_SoundSystem->Play(id, volume, type);
	}

	void SDLSoundSystem::ClearSounds()
	{
		m_SoundSystem->ClearSounds();
	}

	int SDLSoundSystem::MaxVolume() const
	{
		return m_SoundSystem->MaxVolume();
	}
}