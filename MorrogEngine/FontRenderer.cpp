#include <stdexcept>

#include <SDL_ttf.h>

#include "FontRenderer.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

namespace MoE
{
	FontRenderer::FontRenderer(GameObject* const owner, const std::string& fontPath, unsigned int fontSize)
		: FontRenderer{ owner, ResourceManager::Get().LoadFont(fontPath, fontSize) }
	{
	}

	FontRenderer::FontRenderer(GameObject* const owner, std::shared_ptr<Font> font, const std::string& text)
		: Component{ owner }
		, m_Text{ text }
		, m_TextColor{ 255, 255, 255, 255 }
		, m_RenderForQuality{}
		, m_Font{ font }
		, m_FontTexture{}
	{
		RemakeFontTexture();
	}

	FontRenderer::~FontRenderer() = default;

	void FontRenderer::Render() const
	{
		if (!m_FontTexture) return;

		const Renderer& renderer{ Renderer::Get() };
		const glm::vec2& renderPos{ GetOwner()->GetWorldPosition() };
		const glm::ivec2& textureSize{ m_FontTexture->GetSize() };
		const SDL_Rect destRect
		{
			static_cast<int>(renderPos.x),
			static_cast<int>(renderPos.y),
			textureSize.x,
			textureSize.y
		};

		renderer.RenderTexture(*m_FontTexture, destRect);
	}

	void FontRenderer::SetText(const std::string& text)
	{
		m_Text = text;
		RemakeFontTexture();
	}

	void FontRenderer::SetFontSize(unsigned int size)
	{
		m_Font->SetFontSize(size);
		RemakeFontTexture();
	}

	void FontRenderer::SetColor(SDL_Color color)
	{
		m_TextColor = color;
		RemakeFontTexture();
	}

	void FontRenderer::SetRenderForQuality(bool boolean)
	{
		m_RenderForQuality = boolean;
		RemakeFontTexture();
	}

	const std::string& FontRenderer::GetText() const
	{
		return m_Text;
	}

	// Private //

	void FontRenderer::RemakeFontTexture()
	{
		//SDL_Surface* surface{ TTF_RenderText_Blended_Wrapped(m_Font->GetFont(), m_Text.c_str(), m_TextColor, 9999)};
		
		// TTF_RenderText_Solid -> faster but less quality
		// TTF_RenderText_Shaded
		// TTF_RenderText_Blended -> slower but more quality
		// TTF_RenderText_LCD

		SDL_Surface* surface{};

		if (m_RenderForQuality)
		{
			surface = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_TextColor);
			if (!surface)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
		}
		else
		{
			surface = TTF_RenderText_Solid(m_Font->GetFont(), m_Text.c_str(), m_TextColor);
			if (!surface)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
		}

		SDL_Texture* texture{ SDL_CreateTextureFromSurface(Renderer::Get().GetSDLRenderer(), surface) };
		if (!texture)
		{
			SDL_FreeSurface(surface);
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		m_FontTexture = std::make_unique<Texture2D>(texture);
		
		SDL_FreeSurface(surface);
	}
}