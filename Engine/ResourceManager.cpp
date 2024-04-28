#include <stdexcept>
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Font.h"
#include "SoundEffect.h"
#include "MusicPlayer.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	return std::make_shared<Texture2D>(m_DataPath + file);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

std::shared_ptr<SoundEffect> ResourceManager::LoadSoundEffect(const std::string& file) const
{
	return std::make_shared<SoundEffect>(m_DataPath + file);
}

std::shared_ptr<MusicPlayer> ResourceManager::LoadMusicPlayer(const std::string& file) const
{
	return std::make_shared<MusicPlayer>(m_DataPath + file);
}