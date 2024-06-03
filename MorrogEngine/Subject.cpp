#include "Subject.h"
#include "Observer.h"

namespace MoE
{
	void Subject::RegisterObserver(Observer* observer)
	{
		if(observer) m_Observers.emplace_back(observer);
	}

	void Subject::UnRegisterObserver(Observer* observer)
	{
		if (observer)
		{
			m_Observers.erase(std::remove_if(m_Observers.begin(), m_Observers.end(),
				[&](const auto& observerPtr)
				{
					return observerPtr == observer;
				}
			), m_Observers.end());
		}
	}

	Subject::Subject()
		: m_Observers{}
	{
	}

	void Subject::Notify(GameObject* gameObj, EventID eventID)
	{
		for (const auto& observer : m_Observers)
		{
			observer->OnNotify(gameObj, eventID);
		}
	}
}