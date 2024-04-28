#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

Font::Font(const std::string& filePath, unsigned int size)
	: m_Font{ nullptr }
	, m_FilePath{ filePath }
	, m_Size{ size }
{
	m_Font = TTF_OpenFont(m_FilePath.c_str(), m_Size);
	if (!m_Font) throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}

TTF_Font* Font::GetFont() const
{
	return m_Font;
}

void Font::SetSize(unsigned int newSize)
{
	_TTF_Font* tempFont{ nullptr };
	tempFont = TTF_OpenFont(m_FilePath.c_str(), newSize);

	if (!tempFont)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
		return;
	}

	TTF_CloseFont(m_Font);
	m_Font = nullptr;
	m_Size = newSize;
	m_Font = tempFont;
}