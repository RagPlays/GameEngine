#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glm.hpp>

struct SDL_Texture;

class Texture2D final
{
public:

	explicit Texture2D(const std::string& filePath);
	explicit Texture2D(SDL_Texture* texture);
	~Texture2D();

	Texture2D(const Texture2D& other) = delete;
	Texture2D(Texture2D&& other) noexcept = delete;
	Texture2D& operator=(const Texture2D& other) = delete;
	Texture2D& operator=(const Texture2D&& other) noexcept = delete;

	SDL_Texture* GetSDLTexture() const;
	glm::ivec2 GetSize() const;

private:

	SDL_Texture* m_Texture;

};

#endif // !TEXTURE2D_H