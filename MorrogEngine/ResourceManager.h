#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>

#include "Singleton.h"

namespace MoE
{
	class Texture2D;
	class Font;
	class MusicPlayer;
	class SoundEffect;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:

		virtual ~ResourceManager() = default;

		ResourceManager(const ResourceManager& other) = delete;
		ResourceManager(ResourceManager&& other) noexcept = delete;
		ResourceManager& operator=(const ResourceManager& other) = delete;
		ResourceManager& operator=(ResourceManager&& other) noexcept = delete;

		void Init(const std::string& data);

		std::string GetFullPath(const std::string& filename) const;

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		std::unique_ptr<SoundEffect> LoadSoundEffect(const std::string& file) const;
		std::unique_ptr<MusicPlayer> LoadMusicPlayer(const std::string& file) const;

	private:

		friend class MoE::Singleton<ResourceManager>;
		ResourceManager();

	private:

		std::string m_DataPath;

	};
}

#endif // !RESOURCEMANAGER_H