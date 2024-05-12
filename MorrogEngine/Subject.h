#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>

namespace MoE
{
	class Observer;
	class GameObject;
	enum class GameEvent;

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
}

#endif // !SUBJECT_H