#include <stdexcept>

// ImGui
#include <imgui_plot.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>

#include "Renderer.h"

#include "SceneManager.h"
#include "ImGuiRenderer.h"
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

Renderer::Renderer()
	: m_Window{}
	, m_Renderer{}
	, m_ClearColor{}
{
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

	InitImGui();
}

void Renderer::Render() const
{
	// Clear Screen With ClearColor
	SDL_SetRenderDrawColor(m_Renderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
	SDL_RenderClear(m_Renderer);

	// Render All Objects
	SceneManager::Get().Render();

	// Render ImGui
	ImGuiRenderer::Get().Render();
	
	// Sent Data To Monitor Memory
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	DestroyImGui();

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

void Renderer::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void Renderer::DestroyImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}