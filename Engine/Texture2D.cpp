#include <SDL.h>
#include "Texture2D.h"

Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

glm::ivec2 Texture2D::GetSize() const
{
	int w, h;
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &w, &h);
	return { w, h };
}