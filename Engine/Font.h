#ifndef FONT_H
#define FONT_H

#include <string>

struct _TTF_Font;

/**
* Simple RAII wrapper for a _TTF_Font
*/
class Font final
{
public:
	explicit Font(const std::string& filePath, unsigned int size);
	~Font();
	Font(const Font&) = delete;
	Font(Font&&) = delete;
	Font& operator= (const Font&) = delete;
	Font& operator= (const Font&&) = delete;

	// Getters
	_TTF_Font* GetFont() const;

	// Setters
	void SetSize(unsigned int newSize);

private:

	std::string m_FilePath;
	_TTF_Font* m_Font;
	unsigned int m_Size;
};

#endif // !FONT_H