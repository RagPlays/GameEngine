#ifndef FONT_H
#define FONT_H

#include <string>

struct _TTF_Font;

class Font final
{
public:

	explicit Font(const std::string& filePath, unsigned int size);
	~Font();

	Font(const Font& other) = delete;
	Font(Font&& other) noexcept = delete;
	Font& operator=(const Font& other) = delete;
	Font& operator=(const Font&& other) noexcept = delete;

	_TTF_Font* GetFont() const;
	void SetSize(unsigned int newSize);

private:

	const std::string m_FilePath;
	_TTF_Font* m_Font;
	unsigned int m_Size;

};

#endif // !FONT_H