#ifndef STRUCTS_H
#define STRUCTS_H

#include <glm.hpp>

struct Rectf
{
	Rectf() = default;
	explicit Rectf(float x, float y, float width, float height);
	explicit Rectf(const glm::vec2& pos, const glm::vec2& size);

	glm::vec2 pos;
	glm::vec2 size;
};

struct Linef
{
	Linef() = default;
	explicit Linef(const glm::vec2& pointOne, const glm::vec2& pointTwo);

	glm::vec2 pointOne;
	glm::vec2 pointTwo;
};

#endif // !STRUCTS_H
