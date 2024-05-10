#include <stdexcept>
#include <SDL.h>

#include "Renderer.h"

#include "SceneManager.h"
#include "Texture2D.h"

// ImGui
#if defined _DEBUG || defined DEBUG
#include <imgui_plot.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include "ImGuiRenderer.h"
#endif

// Init
void Renderer::Init(SDL_Window* window)
{
	m_pWindow = window;
	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	InitImGui();
}

void Renderer::Render() const
{
	assert(m_pWindow);
	assert(m_pRenderer);

	// Clear Screen With ClearColor
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 1);
	SDL_RenderClear(m_pRenderer);
	SDL_RenderFlush(m_pRenderer);

	// Render All Objects
	SceneManager::Get().Render();

#if defined _DEBUG || defined DEBUG
	// Render ImGui
	ImGuiRenderer::Get().Render();
#endif
	
	// Sent Data To Monitor Memory
	SDL_RenderPresent(m_pRenderer);
}

void Renderer::Destroy()
{
	DestroyImGui();

	if (m_pRenderer)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

// Render Textures
void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &destRect);
}

void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect);
}

// Getters / Setters
SDL_Renderer* Renderer::GetSDLRenderer() const 
{ 
	return m_pRenderer; 
}

// Private Functions //

Renderer::Renderer()
	: m_pWindow{}
	, m_pRenderer{}
{
}

int Renderer::GetOpenGLDriverIndex()
{
	int openglIndex = -1;
	const int driverCount{ SDL_GetNumRenderDrivers() };
	for (int idx{}; idx < driverCount; ++idx)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(idx, &info))
		{
			if (!strcmp(info.name, "opengl"))
			{
				openglIndex = idx;
			}
		}
	}
	return openglIndex;
}

void Renderer::InitImGui()
{
#if defined _DEBUG || defined DEBUG
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
#endif
}

void Renderer::DestroyImGui()
{
#if defined _DEBUG || defined DEBUG
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
#endif
}