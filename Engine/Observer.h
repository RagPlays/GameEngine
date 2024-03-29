#ifndef OBSERVER_H
#define OBSERVER_H

#include "GameEvents.h"

class GameObject;

class Observer
{
public:

	virtual ~Observer() = default;

	Observer(const Observer& other) = delete;
	Observer(Observer&& other) noexcept = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) noexcept = delete;

	virtual void OnNotify(GameObject* gameObj, GameEvent event) = 0;

protected:

	Observer() = default;

};

#endif // !OBSERVER_H