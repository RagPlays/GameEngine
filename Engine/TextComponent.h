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
	explicit TextComponent(GameObject* const owner, std::shared_ptr<Font> font, const std::string& text = "Empty", SDL_Color textColor = {255, 255, 255} );
	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) noexcept = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) noexcept = delete;

	virtual void Update() override;

	void SetText(const std::string& newText);
	void SetFont(std::shared_ptr<Font> newFont);
	void SetColor(SDL_Color newColor);

private:

	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	SDL_Color m_TextColor;
};

#endif // !TEXTCOMPONENT_H