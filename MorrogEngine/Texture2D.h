#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glm.hpp>

struct SDL_Texture;

namespace MoE
{
	class Texture2D final
	{
	public:

		explicit Texture2D(const std::string& filePath);
		explicit Texture2D(SDL_Texture* const texture);
		~Texture2D();

		Texture2D(const Texture2D& other) = delete;
		Texture2D(Texture2D&& other) noexcept = delete;
		Texture2D& operator=(const Texture2D& other) = delete;
		Texture2D& operator=(const Texture2D&& other) noexcept = delete;

		SDL_Texture* GetSDLTexture() const;
		const glm::ivec2& GetSize() const;

	private:

		SDL_Texture* const m_pTexture;
		glm::ivec2 m_Size;

	};
}

#endif // !TEXTURE2D_H