#include <stdexcept>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"

TextComponent::TextComponent(GameObject* const owner, std::shared_ptr<Font> font, const std::string& text, SDL_Color textColor)
	: Component{ owner }
	, m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_Font{ std::move(font) }
	, m_TextColor{ textColor }
{
}

void TextComponent::Update()
{
	if (m_NeedsUpdate && GetOwner()->HasComponent<RenderComponent>())
	{
		SDL_Surface* surface{ TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_TextColor) };
		if (!surface) throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

		SDL_Texture* texture{ SDL_CreateTextureFromSurface(Renderer::Get().GetSDLRenderer(), surface) };
		if (!texture) throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

		GetOwner()->GetComponent<RenderComponent>()->SetTexture(std::make_shared<Texture2D>(texture));

		SDL_FreeSurface(surface);
		m_NeedsUpdate = false;
	}
}

void TextComponent::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(std::shared_ptr<Font> newFont)
{
	m_Font = newFont;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(SDL_Color newColor)
{
	m_TextColor = newColor;
	m_NeedsUpdate = true;
}