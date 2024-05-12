#include "Structs.h"

namespace MoE
{
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
}