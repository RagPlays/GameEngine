#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture2D.h"
#include "Renderer.h"

namespace MoE
{
	Texture2D::Texture2D(const std::string& filePath)
		: Texture2D{ IMG_LoadTexture(Renderer::Get().GetSDLRenderer(), filePath.c_str()) }
	{
	}

	Texture2D::Texture2D(SDL_Texture* const texture)
		: m_pTexture{ texture }
		, m_Size{}
	{
		if (!m_pTexture) std::cerr << "ERROR::TEXTURE2D::COULD_NOT_LOAD_TEXTURE2D_FROM_FILE\n";
		else SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Size.x, &m_Size.y);
	}

	Texture2D::~Texture2D()
	{
		if (m_pTexture) SDL_DestroyTexture(m_pTexture);
	}

	SDL_Texture* Texture2D::GetSDLTexture() const
	{
		return m_pTexture;
	}

	const glm::ivec2& Texture2D::GetSize() const
	{
		return m_Size;
	}
}