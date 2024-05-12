#include <stdexcept>
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Font.h"
#include "SoundEffect.h"
#include "MusicPlayer.h"

namespace MoE
{
	void ResourceManager::Init(const std::string& dataPath)
	{
		m_DataPath = dataPath;
	}

	std::string ResourceManager::GetFullPath(const std::string& filename) const
	{
		return std::string{ m_DataPath + filename };
	}

	std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
	{
		return std::make_shared<Texture2D>(m_DataPath + file);
	}

	std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
	{
		return std::make_shared<Font>(m_DataPath + file, size);
	}

	std::unique_ptr<SoundEffect> ResourceManager::LoadSoundEffect(const std::string& file) const
	{
		return std::make_unique<SoundEffect>(m_DataPath + file);
	}

	std::unique_ptr<MusicPlayer> ResourceManager::LoadMusicPlayer(const std::string& file) const
	{
		return std::make_unique<MusicPlayer>(m_DataPath + file);
	}
}