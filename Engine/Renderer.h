#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL.h>
#include "Singleton.h"

struct SDL_Color;
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

	const SDL_Color& GetBackgroundColor() const;
	void SetBackgroundColor(const SDL_Color& color);

private:

	friend class Singleton<Renderer>;
	Renderer();

	void InitImGui();
	void DestroyImGui();

private:

	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;
	SDL_Color m_ClearColor;
};

#endif // !RENDERER_H