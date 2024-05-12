#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "Singleton.h"

struct SDL_Rect;
struct SDL_Color;
struct SDL_Window;
struct SDL_Renderer;

namespace MoE
{
	class Texture2D;
	class RenderComponent;

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

		void RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) const;

		SDL_Renderer* GetSDLRenderer() const;

	private:

		friend class MoE::Singleton<Renderer>;
		Renderer();

		int GetOpenGLDriverIndex();

		void InitImGui();
		void DestroyImGui();

	private:

		SDL_Renderer* m_pRenderer;
		SDL_Window* m_pWindow;

	};
}

#endif // !RENDERER_H