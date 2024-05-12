#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

namespace MoE
{
	enum class GameEvent
	{
		gameStarts,
		gameEnds,
		levelLoaded,
		playerJoined,
		playerDied,
		foundSmallPickup,
		foundLargePickup
	};
}

#endif // !GAMEEVENTS_H