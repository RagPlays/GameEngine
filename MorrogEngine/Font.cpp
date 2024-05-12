#include <stdexcept>
#include <SDL_ttf.h>

#include "Font.h"

namespace MoE
{
	Font::Font(const std::string& filePath, size_t size)
		: m_pFont{ nullptr }
	{
		if (m_pFont = TTF_OpenFont(filePath.c_str(), static_cast<int>(size)); !m_pFont)
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
}