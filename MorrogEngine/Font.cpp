#include <stdexcept>
#include <SDL_ttf.h>

#include "Font.h"

namespace MoE
{
	Font::Font(const std::string& filePath, unsigned int size)
		: m_pFont{ TTF_OpenFont(filePath.c_str(), static_cast<int>(size)) }
	{
		if (!m_pFont)
		{
			throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
		}
	}

	Font::~Font()
	{
		if (m_pFont) TTF_CloseFont(m_pFont);
	}

	TTF_Font* Font::GetFont() const
	{
		return m_pFont;
	}

	void Font::SetFontSize(unsigned int size)
	{
		const std::string filePath{ TTF_FontFaceFamilyName(m_pFont) };

		TTF_CloseFont(m_pFont);
		m_pFont = nullptr;

		m_pFont = TTF_OpenFont(filePath.c_str(), static_cast<int>(size));
		if (!m_pFont)
		{
			throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
		}
	}
}