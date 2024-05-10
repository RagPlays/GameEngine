#ifndef LEVELRENDERER_H
#define LEVELRENDERER_H

#include <string>
#include <vector>
#include <memory>

#include "Component.h"

class GameObject;
class Texture2D;

struct RenderTile
{

	// maximum grid size of 256x256
	uint8_t gridX;
	uint8_t gridY;
	// maximum texture size of (256*TileSourceSize)x(256*TileSourceSize)
	uint8_t srcGridX;
	uint8_t srcGridY;

};

class LevelRenderer final : public Component
{
public:

	explicit LevelRenderer(GameObject* const owner, const std::string& renderLoadPath, std::shared_ptr<Texture2D> texture);
	~LevelRenderer() = default;

	virtual void Render() const override;

private:

	void LoadLevel();

private:

	uint8_t m_TileDrawSize;
	uint8_t m_TileSourceSize;
	bool m_IsLoaded;
	std::string m_FilePath;
	std::vector<RenderTile> m_LevelTiles;
	std::shared_ptr<Texture2D> m_TileMapTexture;

};

#endif // !LEVELRENDERER_H