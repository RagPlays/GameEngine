#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "Component.h"

class GameObject;
class Texture2D;

class RenderComponent final : public Component
{
public:

	explicit RenderComponent(GameObject* const owner);
	explicit RenderComponent(GameObject* const owner, const std::string& fileName);
	explicit RenderComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture);
	virtual ~RenderComponent() = default;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) noexcept = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

	void SetTextureFromFileName(const std::string& fileName);
	void SetTexture(std::shared_ptr<Texture2D> newTexture);

	void SetDefaultDimentions();
	void SetTextureWidth(int width);
	void SetTextureHeight(int height);
	void SetTextureDimentions(int width, int height);
	void SetTextureDimentions(const glm::ivec2& dimentions);

	virtual void Render() const override;

private:

	glm::ivec2 m_RenderDimentions;
	std::shared_ptr<Texture2D> m_Texture;

};

#endif // !TEXTURECOMPONENT_H