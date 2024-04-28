#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

enum class GameEvent
{
	gameStarts,
	gameEnds,
	playerJoined,
	playerDied,
	foundSmallPickup,
	foundLargePickup
};

#endif // !GAMEEVENTS_H