#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>

#include "Singleton.h"

#include "Structs.h"

struct SDL_Rect;
struct SDL_FRect;
struct SDL_Color;
struct SDL_Window;
struct SDL_Renderer;

namespace MoE
{
	class Texture2D;
	class RenderComponent;

	struct Rectf;
	struct Recti;
	struct Linef;
	struct Linei;
	struct Color;

	class Renderer final : public Singleton<Renderer>
	{
	public:

		virtual ~Renderer() = default;

		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) noexcept = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) noexcept = delete;

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		const Color& GetCurrentDrawColor() const;
		void SetCurrentDrawColor(const Color& color);

		void RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_FRect& destRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_FRect& destRect, const SDL_Rect& srcRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& destRect, const SDL_Rect& srcRect, SDL_RendererFlip flip) const;

		void RenderPoint(const Pointf& point);
		void RenderPoint(const Pointi& point);

		void RenderLine(const Linef& line);
		void RenderLine(const Linei& line);

		void RenderRect(const Rectf& rect, bool filled);
		void RenderRect(const Recti& rect, bool filled);

		SDL_Renderer* GetSDLRenderer() const;

	private:

		friend class MoE::Singleton<Renderer>;
		Renderer();

		int GetOpenGLDriverIndex();

		void InitImGui();
		void DestroyImGui();

		void SetCurrentColor() const;
		void SetBackgroundColor() const;

	private:

		SDL_Renderer* m_pRenderer;
		SDL_Window* m_pWindow;

		Color m_BackgroundColor;
		Color m_CurrentDrawColor;
	};
}

#endif // !RENDERER_H