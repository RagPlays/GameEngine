#include "TextureRenderer.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"

namespace MoE
{
	TextureRenderer::TextureRenderer(GameObject* const owner)
		: TextureRenderer{ owner, std::shared_ptr<Texture2D>{} }
	{
	}

	TextureRenderer::TextureRenderer(GameObject* const owner, std::shared_ptr<Texture2D> texture)
		: Component{ owner }
		, m_Texture{ texture }
		, m_RenderDimensions{}
		, m_SrcRect{}
		, m_FlipMode{ SDL_RendererFlip::SDL_FLIP_NONE }
	{
		if (m_Texture != nullptr)
		{
			SetDefaultDimensions();
			SetDefaultSourceRect();
		}
	}

	void TextureRenderer::SetTexture(std::shared_ptr<Texture2D> texture)
	{
		if (texture != nullptr)
		{
			m_Texture = texture;
			SetDefaultDimensions();
		}
	}

	void TextureRenderer::SetTexture(std::shared_ptr<Texture2D> texture, const glm::ivec2& dimentions)
	{
		if (texture != nullptr)
		{
			m_Texture = texture;
			SetTextureDimensions(dimentions);
		}
	}

	void TextureRenderer::SetFlipMode(SDL_RendererFlip flip)
	{
		m_FlipMode = flip;
	}

	void TextureRenderer::SetDefaultDimensions()
	{
		m_RenderDimensions = m_Texture->GetSize();
	}

	void TextureRenderer::SetTextureWidth(int width)
	{
		m_RenderDimensions.x = width;
	}

	void TextureRenderer::SetTextureHeight(int height)
	{
		m_RenderDimensions.y = height;
	}

	void TextureRenderer::SetTextureDimensions(const glm::ivec2& dimentions)
	{
		m_RenderDimensions = dimentions;
	}

	void TextureRenderer::ScaleTextureDimensions(float scale)
	{
		m_RenderDimensions *= scale;
	}

	int TextureRenderer::GetTextureWidth() const
	{
		return m_RenderDimensions.x;
	}

	int TextureRenderer::GetTextureHeight() const
	{
		return  m_RenderDimensions.y;
	}

	const glm::ivec2& TextureRenderer::GetTextureDimentions() const
	{
		return m_RenderDimensions;
	}

	void TextureRenderer::SetDefaultSourceRect()
	{
		const glm::ivec2& dimentions{ m_Texture->GetSize() };
		m_SrcRect = SDL_Rect{ 0, 0, dimentions.x, dimentions.y };
	}

	void TextureRenderer::SetSourceRect(int x, int y, int width, int height)
	{
		SetSourceRect(SDL_Rect{ x, y, width, height });
	}

	void TextureRenderer::SetSourceRect(const SDL_Rect& srcRect)
	{
		m_SrcRect = srcRect;
	}

	void TextureRenderer::Render() const
	{
		if (!m_Texture) return;

		const Renderer& renderer{ Renderer::Get() };
		const glm::vec2& renderPos{ GetOwner()->GetWorldPosition() };
		const SDL_Rect destRect
		{
			static_cast<int>(renderPos.x),
			static_cast<int>(renderPos.y),
			m_RenderDimensions.x,
			m_RenderDimensions.y
		};

		renderer.RenderTexture(*m_Texture, destRect, m_SrcRect, m_FlipMode);
	}
}