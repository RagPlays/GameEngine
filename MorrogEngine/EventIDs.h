#ifndef EVENTIDS_H
#define EVENTIDS_H

enum Event
{
	sceneStarts = 0,
	gameEnds,
	levelCompleted,
	levelLoaded,
	playerJoined,
	playerDied,
	foundSmallPickup,
	foundLargePickup
};

#endif // !EVENTIDS_H