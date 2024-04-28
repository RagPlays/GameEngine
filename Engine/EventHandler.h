#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "GameEvents.h"

class EventHandler
{
public:

	EventHandler() = default;
	virtual ~EventHandler() = default;

	EventHandler(const EventHandler& other) = delete;
	EventHandler(EventHandler&& other) noexcept = delete;
	EventHandler& operator=(const EventHandler& other) = delete;
	EventHandler& operator=(EventHandler&& other) noexcept = delete;

	virtual void HandleEvent(GameEvent gameEvent) = 0;

};

#endif // !EVENTHANDLER_H