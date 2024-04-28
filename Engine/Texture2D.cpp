#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Renderer.h"

Texture2D::Texture2D(const std::string& filePath)
	: m_Texture{ IMG_LoadTexture(Renderer::Get().GetSDLRenderer(), filePath.c_str()) }
{
	if (!m_Texture)
	{
		std::cerr << "ERROR::TEXTURE2D::COULD_NOT_LOAD_TEXTURE2D_FROM_FILE\n";
	}
}

Texture2D::Texture2D(SDL_Texture* texture)
	: m_Texture{ texture }
{
}

Texture2D::~Texture2D()
{
	if(m_Texture) SDL_DestroyTexture(m_Texture);
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