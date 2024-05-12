#ifndef FONT_H
#define FONT_H

#include <string>

struct _TTF_Font;

class Font final
{
public:

	explicit Font(const std::string& filePath, size_t size);
	~Font();

	Font(const Font& other) = delete;
	Font(Font&& other) noexcept = delete;
	Font& operator=(const Font& other) = delete;
	Font& operator=(Font&& other) noexcept = delete;

	_TTF_Font* GetFont() const;

private:

	_TTF_Font* m_pFont;

};

#endif // !FONT_H