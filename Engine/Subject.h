#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>
#include "Observer.h"

class Observer;
class GameObject;

class Subject
{
public:

	virtual ~Subject() = default;

	void RegisterObserver(Observer* observer);
	void UnRegisterObserver(Observer* observer);

protected:

	Subject() = default;
	
	void Notify(GameObject* gameObj, GameEvent gameEvent);

private:
	std::vector<Observer*> m_Observers;
};

#endif // !SUBJECT_H