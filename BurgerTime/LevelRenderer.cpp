#include <fstream>
#include <iostream>
#include "LevelRenderer.h"
#include "Renderer.h"
#include "ResourceManager.h"

LevelRenderer::LevelRenderer(GameObject* const owner, const std::string& renderLevelLoadPath, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
	, m_LoadFilePath{ renderLevelLoadPath }
	, m_TileMapTexture{ texture }
	, m_IsLoaded{ false }
{
	LoadLevel();
}

void LevelRenderer::Render() const
{
	const Renderer& renderer{ Renderer::Get() };

	for (auto& tileInfo : m_LevelTiles)
	{
		SDL_Rect destRect
		{
			tileInfo.gridX * m_TileDrawSize,
			tileInfo.gridY * m_TileDrawSize,
			m_TileDrawSize,
			m_TileDrawSize
		};
		SDL_Rect sourceRect
		{
			tileInfo.srcRectX * m_TileSourceSize,
			tileInfo.srcRectY * m_TileSourceSize,
			m_TileSourceSize,
			m_TileSourceSize
		};
		renderer.RenderTexture(*m_TileMapTexture, destRect, sourceRect);
	}
}

void LevelRenderer::LoadLevel()
{
	m_LevelTiles.clear();

	////// FILE STRUCTURE //////
	// map width (unsigned int)
	// map height (unsigned int)
	// tileDrawSize
	// tileSourceSize
	//
	// gridX gridY srcX srcY
	// gridX gridY srcX srcY
	// gridX gridY srcX srcY
	// .....
	////////////////////////////

	const std::string pathName{ ResourceManager::Get().GetFullPath(m_LoadFilePath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELRENDERER::COULD_NOT_LOAD_TILEMAP_FROM_FILE: " << pathName << "\n";
		m_IsLoaded = false;
		return;
	}
	else
	{
		int mapWidth{};
		int mapHeight{};
		int tileDrawSize{};
		int tileSourceSize{};

		if (inFile >> mapWidth >> mapHeight >> tileDrawSize >> tileSourceSize)
		{
			m_LevelTiles.reserve(static_cast<size_t>(mapWidth * mapHeight));
			m_TileDrawSize = static_cast<uint8_t>(tileDrawSize); // source x 3 ?
			m_TileSourceSize = static_cast<uint8_t>(tileSourceSize); // 16x16 ?
		}
		else return;

		int gridX{};
		int gridY{};
		int srcRectX{};
		int srcRectY{};

		while (inFile >> gridX >> gridY >> srcRectX >> srcRectY)
		{
			if (inFile)
			{
				if (gridX >= mapWidth || gridY >= mapHeight)
				{
					std::cerr << "ERROR::LEVELRENDERER::LEVELFILE_NOT_SET_CORRECTLY!\n";
					return;
				}
				m_LevelTiles.emplace_back(
					RenderTile{ 
						static_cast<uint8_t>(gridX),
						static_cast<uint8_t>(gridY),
						static_cast<uint16_t>(srcRectX),
						static_cast<uint16_t>(srcRectY)
					}
				);
			}
			else return;
		}
	}

	if (!m_LevelTiles.empty())
	{
		m_IsLoaded = true;
	}
}