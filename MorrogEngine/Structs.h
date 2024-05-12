#ifndef STRUCTS_H
#define STRUCTS_H

#include <glm.hpp>

namespace MoE
{
	struct Rectf
	{
		Rectf() = default;
		explicit Rectf(float x, float y, float width, float height);
		explicit Rectf(const glm::vec2& pos, const glm::vec2& size);

		glm::vec2 pos;
		glm::vec2 size;
	};

	struct Recti
	{
		Recti() = default;
		explicit Recti(int x, int y, int width, int height);
		explicit Recti(const glm::ivec2& pos, const glm::ivec2& size);

		glm::ivec2 pos;
		glm::ivec2 size;
	};

	struct Linef
	{
		Linef() = default;
		explicit Linef(float x1, float y1, float x2, float y2);
		explicit Linef(const glm::vec2& pointOne, const glm::vec2& pointTwo);

		glm::vec2 pointOne;
		glm::vec2 pointTwo;
	};

	struct Linei
	{
		Linei() = default;
		explicit Linei(int x1, int y1, int x2, int y2);
		explicit Linei(const glm::ivec2& pointOne, const glm::ivec2& pointTwo);

		glm::ivec2 pointOne;
		glm::ivec2 pointTwo;
	};
}

#endif // !STRUCTS_H
