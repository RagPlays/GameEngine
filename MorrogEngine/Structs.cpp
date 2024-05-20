#include "Structs.h"

namespace MoE
{
	// LINEF / LINEI //

	Linef::Linef(float x1, float y1, float x2, float y2)
		: pointOne{ x1, y1 }
		, pointTwo{ x2, y2 }
	{
	}

	Linef::Linef(const glm::vec2& pointOne, const glm::vec2& pointTwo)
		: pointOne{ pointOne }
		, pointTwo{ pointTwo }
	{
	}

	Linei::Linei(int x1, int y1, int x2, int y2)
		: pointOne{ x1, y1 }
		, pointTwo{ x2, y2 }
	{
	}

	Linei::Linei(const glm::ivec2& pointOne, const glm::ivec2& pointTwo)
		: pointOne{ pointOne }
		, pointTwo{ pointTwo }
	{
	}

	// RECTF / RECTI //

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

	Recti::Recti(int x, int y, int width, int height)
		: pos{ x, y }
		, size{ width, height }
	{
	}

	Recti::Recti(const glm::ivec2& pos, const glm::ivec2& size)
		: pos{ pos }
		, size{ size }
	{
	}

	// CIRCLEF / CIRCLEI //

	Circlef::Circlef()
		: Circlef{ 0.f, 0.f, 0.f }
	{
	}

	Circlef::Circlef(const Point2f& center, float radius)
		: center{ center }
		, radius{ radius }
	{
	}

	Circlef::Circlef(float centerX, float centerY, float radius)
		: center{ centerX, centerY }
		, radius{ radius }
	{
	}

	Circlei::Circlei()
		: Circlei{ 0, 0, 0 }
	{
	}

	Circlei::Circlei(const Point2i& center, float radius)
		: center{ center }
		, radius{ radius }
	{
	}

	Circlei::Circlei(float centerX, float centerY, float radius)
		: center{ centerX, centerY }
		, radius{ radius }
	{
	}

	// COLOR //

	Color::Color(uint8_t r, uint8_t g, uint8_t b)
		: r{ r }
		, g{ g }
		, b{ b }
		, a{ 255 }
	{
	}

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: r{ r }
		, g{ g }
		, b{ b }
		, a{ a }
	{
	}
}