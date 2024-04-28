#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>
#include "Singleton.h"

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
	std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	std::shared_ptr<SoundEffect> LoadSoundEffect(const std::string& file) const;
	std::shared_ptr<MusicPlayer> LoadMusicPlayer(const std::string& file) const;

private:

	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

private:

	std::string m_DataPath;

};

#endif // !RESOURCEMANAGER_H