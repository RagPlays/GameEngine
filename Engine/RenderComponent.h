#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <memory>

#include <glm.hpp>
#include <SDL.h>
#include "Component.h"

class GameObject;
class Texture2D;

class RenderComponent final : public Component
{
public:

	explicit RenderComponent(GameObject* const owner);
	explicit RenderComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture);
	virtual ~RenderComponent() = default;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) noexcept = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

	// Texture
	void SetTexture(std::shared_ptr<Texture2D> texture);
	void SetTexture(std::shared_ptr<Texture2D> texture, const glm::ivec2& dimentions);

	// Dimensions
	void SetDefaultDimensions();
	void SetTextureWidth(int width);
	void SetTextureHeight(int height);
	void SetTextureDimensions(const glm::ivec2& dimentions);

	int GetTextureWidth() const;
	int GetTextureHeight() const;
	const glm::ivec2& GetTextureDimentions() const;

	// SrcRect
	void ClearSourceRect();
	void SetSourceRect(int x, int y, int width, int height);
	void SetSourceRect(const SDL_Rect& srcRect);

	virtual void Render() const override;

private:

	std::shared_ptr<Texture2D> m_Texture;
	glm::ivec2 m_RenderDimensions;
	bool m_SrcRectSet;
	SDL_Rect m_SrcRect;
};

#endif // !TEXTURECOMPONENT_H