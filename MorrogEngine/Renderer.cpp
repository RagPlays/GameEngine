#include <stdexcept>

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

namespace MoE
{
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
		SetBackgroundColor();
		SDL_RenderClear(m_pRenderer);
		SDL_RenderFlush(m_pRenderer);
		SetCurrentColor();

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

	const Color& Renderer::GetCurrentDrawColor() const
	{
		return m_CurrentDrawColor;
	}

	void Renderer::SetCurrentDrawColor(const Color& color)
	{
		m_CurrentDrawColor = color;
		SetCurrentColor();
	}

	// Render Textures
	void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const
	{
		SDL_RenderCopy(m_pRenderer, texture.GetSDLTexture(), nullptr, &destRect);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const SDL_FRect& destRect) const
	{
		SDL_RenderCopyF(m_pRenderer, texture.GetSDLTexture(), nullptr, &destRect);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const
	{
		SDL_RenderCopy(m_pRenderer, texture.GetSDLTexture(), &srcRect, &destRect);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const SDL_FRect& destRect, const SDL_Rect& srcRect) const
	{
		SDL_RenderCopyF(m_pRenderer, texture.GetSDLTexture(), &srcRect, &destRect);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& destRect, const SDL_Rect& srcRect, SDL_RendererFlip flip) const
	{
		SDL_RenderCopyEx(m_pRenderer, texture.GetSDLTexture(), &srcRect, &destRect, 0.0, nullptr, flip);
	}

	// Render Shapes
	void Renderer::RenderPoint(const Pointf& point)
	{
		SDL_RenderDrawPointF(m_pRenderer, point.x, point.y);
	}

	void Renderer::RenderPoint(const Pointi& point)
	{
		SDL_RenderDrawPoint(m_pRenderer, point.x, point.y);
	}

	void Renderer::RenderLine(const Linef& line)
	{
		SDL_RenderDrawLineF(m_pRenderer, line.pointOne.x, line.pointOne.y, line.pointTwo.x, line.pointTwo.y);
	}

	void Renderer::RenderLine(const Linei& line)
	{
		SDL_RenderDrawLine(m_pRenderer, line.pointOne.x, line.pointOne.y, line.pointTwo.x, line.pointTwo.y);
	}

	void Renderer::RenderRect(const Rectf& rect, bool filled)
	{
		const SDL_FRect sdlRect{ rect.pos.x, rect.pos.y, rect.size.x, rect.size.y };
		if (filled) SDL_RenderFillRectF(m_pRenderer, &sdlRect);
		else SDL_RenderDrawRectF(m_pRenderer, &sdlRect);
	}

	void Renderer::RenderRect(const Recti& rect, bool filled)
	{
		const SDL_Rect sdlRect{ rect.pos.x, rect.pos.y, rect.size.x, rect.size.y };
		if (filled) SDL_RenderFillRect(m_pRenderer, &sdlRect);
		else SDL_RenderDrawRect(m_pRenderer, &sdlRect);
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
		, m_BackgroundColor{ 0, 0, 0, 255 }
		, m_CurrentDrawColor{ 0, 0, 0, 255 }
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

	void Renderer::SetCurrentColor() const
	{
		SDL_SetRenderDrawColor(m_pRenderer, m_CurrentDrawColor.r, m_CurrentDrawColor.g, m_CurrentDrawColor.b, m_CurrentDrawColor.a);
	}

	void Renderer::SetBackgroundColor() const
	{
		SDL_SetRenderDrawColor(m_pRenderer, m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	}
}