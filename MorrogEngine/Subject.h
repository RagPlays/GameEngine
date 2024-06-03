#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>

namespace MoE
{
	using EventID = int;

	class Observer;
	class GameObject;

	class Subject
	{
	public:

		virtual ~Subject() = default;

		void RegisterObserver(Observer* observer);
		void UnRegisterObserver(Observer* observer);

		void Notify(GameObject* gameObj, EventID eventID);

	protected:

		Subject();

	private:

		std::vector<Observer*> m_Observers;

	};
}

#endif // !SUBJECT_H