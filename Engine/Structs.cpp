#include "Structs.h"

// RECTF //

Rectf::Rectf(float x, float y, float width, float height)
	: pos{ x, y }
	, size{ width, height }
{
}

Rectf::Rectf(const glm::vec2& pos, const glm::vec2& size)
	: pos{ pos }
	, size{ size }
{
}

// LINEF //

Linef::Linef(const glm::vec2& pointOne, const glm::vec2& pointTwo)
	: pointOne{ pointOne }
	, pointTwo{ pointTwo }
{
}