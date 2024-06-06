#ifndef LEVELRENDERER_H
#define LEVELRENDERER_H

#include <string>
#include <vector>
#include <memory>

#include "Component.h"
#include "Structs.h"

namespace MoE
{
	class GameObject;
	class Texture2D;
}

class LevelRenderer final : public MoE::Component
{
public:

	explicit LevelRenderer(MoE::GameObject* const owner, const std::string& renderLoadPath, std::shared_ptr<MoE::Texture2D> texture);
	virtual ~LevelRenderer() = default;

	virtual void Render() const override;

private:

	void LoadTiles(const std::string& filePath);

private:

	struct RenderTile
	{

		// maximum grid size of 256x256
		//uint8_t gridX;
		//uint8_t gridY;
		// maximum texture size of (256*TileSourceSize)x(256*TileSourceSize)
		//uint8_t srcGridX;
		//uint8_t srcGridY;

		MoE::Recti destRect;
		MoE::Recti srcRect;

	};

	uint8_t m_TileDrawSize;
	uint8_t m_TileSourceSize;
	std::vector<RenderTile> m_LevelTiles;
	std::shared_ptr<MoE::Texture2D> m_TileMapTexture;

};

#endif // !LEVELRENDERER_H