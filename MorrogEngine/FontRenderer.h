#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <memory>
#include <string>

#include <SDL.h>

#include "Component.h"

namespace MoE
{
	class Font;
	class Texture2D;
	class GameObject;

	class FontRenderer final : public Component
	{
	public:

		explicit FontRenderer(GameObject* const owner, const std::string& fontPath, unsigned int fontSize);
		explicit FontRenderer(GameObject* const owner, std::shared_ptr<Font> font, const std::string& text = "Empty");
		virtual ~FontRenderer();

		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetFontSize(unsigned int size);
		void SetColor(SDL_Color color);
		void SetRenderForQuality(bool boolean);

		const std::string& GetText() const;

	private:

		void RemakeFontTexture();

	private:

		std::string m_Text;
		SDL_Color m_TextColor;
		bool m_RenderForQuality;
		std::shared_ptr<Font> m_Font;
		std::unique_ptr<Texture2D> m_FontTexture;

	};
}

#endif // !FONTRENDERER_H
