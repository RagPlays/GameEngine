#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

// Global functions
int GetOpenGLDriverIndex()
{
	int openglIndex = -1;
	const int driverCount = SDL_GetNumRenderDrivers();
	for (int i{}; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
		{
			if (!strcmp(info.name, "opengl"))
			{
				openglIndex = i;
			}
		}
	}
	return openglIndex;
}

// Init
void Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render() const
{
	const SDL_Color& color = GetBackgroundColor();

	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

// Render Textures
void Renderer::RenderTexture(const Texture2D& texture, float x, float y) const
{
	SDL_Rect destRect{ static_cast<int>(x), static_cast<int>(y), 0, 0 };
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);
	RenderTexture(texture, destRect);
}

void Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const
{
	RenderTexture(texture, { static_cast<int>(x),static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) });
}

void Renderer::RenderTexture(const Texture2D& texture, int x, int y) const
{
	SDL_Rect destRect{ x, y, 0, 0 };
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);
	RenderTexture(texture, destRect);
}

void Renderer::RenderTexture(const Texture2D& texture, int x, int y, int width, int height) const
{
	RenderTexture(texture, { x, y, width, height });
}

void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &destRect);
}

void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect);
}

// Getters / Setters
SDL_Renderer* Renderer::GetSDLRenderer() const 
{ 
	return m_Renderer; 
}

const SDL_Color& Renderer::GetBackgroundColor() const
{
	return m_ClearColor;
}

void Renderer::SetBackgroundColor(const SDL_Color& color)
{
	m_ClearColor = color;
}