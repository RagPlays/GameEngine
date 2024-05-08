#ifndef LEVELRENDERER_H
#define LEVELRENDERER_H

#include <cstdint>
#include <string>
#include <vector>
#include <glm.hpp>
#include <memory>
#include "Component.h"

class GameObject;
class Texture2D;

struct RenderTile
{
	// maximum grid size of 256x256
	uint8_t gridX;
	uint8_t gridY;
	// maximum texture size of 65.535x65.535 + tilesize on x and y
	uint16_t srcRectX;
	uint16_t srcRectY;
};

class LevelRenderer final : public Component
{
public:

	explicit LevelRenderer(GameObject* const owner, const std::string& renderLevelLoadPath, std::shared_ptr<Texture2D> texture);
	~LevelRenderer() = default;

	virtual void Render() const override;

private:

	void LoadLevel();

private:

	uint8_t m_TileDrawSize;
	uint8_t m_TileSourceSize;
	bool m_IsLoaded;
	std::string m_LoadFilePath;
	std::vector<RenderTile> m_LevelTiles;
	std::shared_ptr<Texture2D> m_TileMapTexture;

};

#endif // !LEVELRENDERER_H
