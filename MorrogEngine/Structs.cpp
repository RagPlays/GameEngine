#include <SDL.h>
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

	Linef::operator Linei() const
	{
		return Linei
		{
			glm::ivec2(pointOne),
			glm::ivec2(pointTwo),
		};
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

	Linei::operator Linef() const
	{
		return Linef
		{
			glm::vec2(pointOne),
			glm::vec2(pointTwo),
		};
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

	Rectf::operator Recti() const
	{
		return Recti
		{
			glm::ivec2(pos),
			glm::ivec2(size)
		};
	}

	Rectf::operator SDL_Rect() const
	{
		return SDL_Rect
		{
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			static_cast<int>(size.x),
			static_cast<int>(size.y),
		};
	}

	Rectf::operator SDL_FRect() const
	{
		return SDL_FRect
		{
			pos.x,
			pos.y,
			size.x,
			size.y
		};
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

	Recti::operator Rectf() const
	{
		return Rectf
		{
			glm::vec2(pos),
			glm::vec2(size)
		};
	}

	Recti::operator SDL_Rect() const
	{
		return SDL_Rect
		{
			pos.x,
			pos.y,
			size.x,
			size.y
		};
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