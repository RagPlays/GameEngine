#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include "Component.h"

namespace MoE
{
	class Font;
	class Texture2D;

	class FontRenderer final : public Component
	{
	public:

		explicit FontRenderer(GameObject* const owner);
		virtual ~FontRenderer() = default;

	private:

		

	};
}

#endif // !FONTRENDERER_H
