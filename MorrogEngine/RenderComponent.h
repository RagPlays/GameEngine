#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <memory>

#include <glm.hpp>
#include <SDL.h>

#include "Component.h"
#include "Structs.h"

namespace MoE
{
	class GameObject;
	class Texture2D;

	class RenderComponent final : public Component
	{
	public:

		explicit RenderComponent(GameObject* const owner);
		explicit RenderComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

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

#endif // !TEXTURECOMPONENT_H