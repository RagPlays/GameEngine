#include <iostream>
#include <fstream>

#include "LevelRenderer.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameManager.h"
#include "LevelManager.h"

using namespace MoE;

LevelRenderer::LevelRenderer(GameObject* const owner, const std::string& renderLoadPath, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
	, m_TileDrawSize{}
	, m_TileSourceSize{}
	, m_LevelTiles{}
	, m_TileMapTexture{ texture }
{
	LoadTiles(renderLoadPath);
}

void LevelRenderer::Render() const
{
	const Renderer& renderer{ Renderer::Get() };

	for (const auto& tileInfo : m_LevelTiles)
	{
		renderer.RenderTexture(*m_TileMapTexture, static_cast<SDL_Rect>(tileInfo.destRect), static_cast<SDL_Rect>(tileInfo.srcRect));
	}
}

void LevelRenderer::LoadTiles(const std::string& filePath)
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

	const std::string pathName{ ResourceManager::Get().GetFullPath(filePath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELRENDERER::COULD_NOT_LOAD_TILEMAP_FROM_FILE: " << pathName << "\n";
		return;
	}
	else
	{
		const uint8_t tileSize{ LevelManager::Get().GetTileSize() };
		int mapWidth{};
		int mapHeight{};

		if (inFile >> mapWidth >> mapHeight)
		{
			m_LevelTiles.reserve(static_cast<size_t>(mapWidth * mapHeight));
			m_TileSourceSize = tileSize; // 16x16 ?  
			m_TileDrawSize = static_cast<uint8_t>(tileSize * GameManager::Get().GetGameScale()); // source x 3 ?
		}
		else return;

		int gridX{};
		int gridY{};
		int srcGridX{};
		int srcGridY{};

		while (inFile >> gridX >> gridY >> srcGridX >> srcGridY)
		{
			if (gridX >= mapWidth || gridY >= mapHeight)
			{
				std::cerr << "ERROR::LEVELRENDERER::LEVELFILE_NOT_SET_CORRECTLY!\n";
				return;
			}
			m_LevelTiles.emplace_back
			(
				RenderTile
				{
					MoE::Recti
					{
						gridX * m_TileDrawSize,
						gridY * m_TileDrawSize,
						m_TileDrawSize,
						m_TileDrawSize
					},
					MoE::Recti
					{
						srcGridX * m_TileSourceSize,
						srcGridY * m_TileSourceSize,
						m_TileSourceSize,
						m_TileSourceSize
					}
				}
			);
		}
	}
}