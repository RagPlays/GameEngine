#include <stdexcept>
#include <SDL_ttf.h>

#include "Font.h"

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

//void Font::SetSize(size_t newSize)
//{
//	if (_TTF_Font* tempFont{ TTF_OpenFont(m_FilePath.c_str(), static_cast<int>(newSize)) }; tempFont)
//	{
//		TTF_CloseFont(m_pFont);
//		m_pFont = tempFont;
//		return;
//	}
//	throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
//}