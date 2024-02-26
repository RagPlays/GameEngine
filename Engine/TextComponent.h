#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "Component.h"

class Font;
class Texture2D;
class GameObject;

class TextComponent final : public Component
{
public:
	explicit TextComponent(GameObject* const owner, const std::string& text, std::shared_ptr<Font> font, SDL_Color textColor = {255, 255, 255} );
	~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) noexcept = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;
	void ForceTextUpdate();

	void SetText(const std::string& newText);
	void SetFont(std::shared_ptr<Font> newFont);
	void SetColor(SDL_Color newColor);

private:

	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_TextTexture;
	SDL_Color m_TextColor;
};

#endif // !TEXTCOMPONENT_H