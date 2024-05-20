#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "Structs.h"

namespace MoE
{
	struct Rectf;
	struct Recti;
	struct Linef;
	struct Linei;

	namespace Coll
	{
		inline bool OverLapping(const Rectf& r1, const Rectf& r2)
		{
			return
				!(
					r1.pos.x + r1.size.x < r2.pos.x ||
					r2.pos.x + r2.size.x < r1.pos.x ||
					r1.pos.y > r2.pos.y + r2.size.y ||
					r2.pos.y > r1.pos.y + r1.size.y
					);
		}

		inline bool LinesIntersecting(const Linei& l1, const Linei& l2)
		{
			const glm::ivec2& p1{ l1.pointOne };
			const glm::ivec2& p2{ l1.pointTwo };
			const glm::ivec2& p3{ l2.pointOne };
			const glm::ivec2& p4{ l2.pointTwo };

			const int p4x_p3x = p4.x - p3.x;
			const int p1y_p3y = p1.y - p3.y;
			const int p4y_p3y = p4.y - p3.y;
			const int p1x_p3x = p1.x - p3.x;
			const int p2x_p1x = p2.x - p1.x;
			const int p2y_p1y = p2.y - p1.y;

			const float denominator{ 1.f / static_cast<float>(p4y_p3y * p2x_p1x - p4x_p3x * p2y_p1y) };

			if (denominator == 0.f) return false;

			const float uA{ static_cast<float>(p4x_p3x * p1y_p3y - p4y_p3y * p1x_p3x) * denominator };
			const float uB{ static_cast<float>(p2x_p1x * p1y_p3y - p2y_p1y * p1x_p3x) * denominator };

			return (uA >= 0.f && uA <= 1.f && uB >= 0.f && uB <= 1.f);
		}
	}
}

#endif // !COLLISIONS_H