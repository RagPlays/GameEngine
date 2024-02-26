#include <stdexcept>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

TextComponent::TextComponent(GameObject* const owner, const std::string& text, std::shared_ptr<Font> font, SDL_Color textColor)
	: Component{ owner }
	, m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_Font{ std::move(font) }
	, m_TextTexture{ nullptr }
	, m_TextColor{ textColor }
{
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		SDL_Surface* surface{ TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_TextColor) };
		if (!surface) throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

		SDL_Texture* texture{ SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface) };
		if (!texture) throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

		SDL_FreeSurface(surface);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_TextTexture && m_TextTexture.get())
	{
		const glm::vec3& renderPos{ m_Owner->GetTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_TextTexture, renderPos.x, renderPos.y);
	}
}

void TextComponent::ForceTextUpdate()
{
	m_NeedsUpdate = true;
}

void TextComponent::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(std::shared_ptr<Font> newFont)
{
	m_Font = newFont;
}

void TextComponent::SetColor(SDL_Color newColor)
{
	m_TextColor = newColor;
	m_NeedsUpdate = true;
}