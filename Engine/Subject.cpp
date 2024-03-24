#include "Subject.h"

void Subject::RegisterObserver(Observer* observer)
{
	m_Observers.emplace_back(std::move(observer));
}

void Subject::UnRegisterObserver(Observer* observer)
{
	m_Observers.erase(std::remove_if(m_Observers.begin(), m_Observers.end(),
		[&](const auto& observerPtr)
		{ 
			return observerPtr == observer; 
		}
	), m_Observers.end());
}

void Subject::Notify(GameObject* gameObj, GameEvent gameEvent)
{
	for (const auto& observer : m_Observers)
	{
		observer->OnNotify(gameObj, gameEvent);
	}
}