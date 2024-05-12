#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Renderer.h"

Texture2D::Texture2D(const std::string& filePath)
	: m_pTexture{ IMG_LoadTexture(Renderer::Get().GetSDLRenderer(), filePath.c_str()) }
{
	if (!m_pTexture)
	{
		std::cerr << "ERROR::TEXTURE2D::COULD_NOT_LOAD_TEXTURE2D_FROM_FILE\n";
	}
}

Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture{ texture }
{
}

Texture2D::~Texture2D()
{
	if(m_pTexture) SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

glm::ivec2 Texture2D::GetSize() const
{
	int w, h;
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &w, &h);
	return { w, h };
}