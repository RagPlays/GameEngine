#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <string>
#include <memory>
#include "Component.h"

class GameObject;
class Texture2D;

class TextureComponent final : public Component
{
public:

	explicit TextureComponent(GameObject* const owner, const std::string& fileName);
	explicit TextureComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture);
	~TextureComponent() = default;

	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) noexcept = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

	virtual void Render() const override;

private:

	std::shared_ptr<Texture2D> m_Texture;
};

#endif // !TEXTURECOMPONENT_H