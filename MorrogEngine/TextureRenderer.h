#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

#include <memory>

#include <glm.hpp>
#include <SDL.h>

#include "Component.h"
#include "Structs.h"

namespace MoE
{
	class GameObject;
	class Texture2D;

	class TextureRenderer final : public Component
	{
	public:

		explicit TextureRenderer(GameObject* const owner);
		explicit TextureRenderer(GameObject* const owner, std::shared_ptr<Texture2D> texture);
		virtual ~TextureRenderer() = default;

		TextureRenderer(const TextureRenderer& other) = delete;
		TextureRenderer(TextureRenderer&& other) noexcept = delete;
		TextureRenderer& operator=(const TextureRenderer& other) = delete;
		TextureRenderer& operator=(TextureRenderer&& other) noexcept = delete;

		// Texture
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetTexture(std::shared_ptr<Texture2D> texture, const glm::ivec2& dimentions);

		// Flips
		void SetFlipMode(SDL_RendererFlip flip);

		// Dimensions
		void SetDefaultDimensions();
		void SetTextureWidth(int width);
		void SetTextureHeight(int height);
		void SetTextureDimensions(const glm::ivec2& dimentions);
		void ScaleTextureDimensions(float scale);

		int GetTextureWidth() const;
		int GetTextureHeight() const;
		const glm::ivec2& GetTextureDimentions() const;

		// SrcRect
		void SetDefaultSourceRect();
		void SetSourceRect(int x, int y, int width, int height);
		void SetSourceRect(const SDL_Rect& srcRect);

		virtual void Render() const override;

	private:


		std::shared_ptr<Texture2D> m_Texture;
		glm::ivec2 m_RenderDimensions;
		SDL_Rect m_SrcRect;
		SDL_RendererFlip m_FlipMode;

	};
}

#endif // !TEXTURERENDERER_H