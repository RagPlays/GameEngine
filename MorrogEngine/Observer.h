#ifndef OBSERVER_H
#define OBSERVER_H

namespace MoE
{
	using EventID = int;

	class GameObject;
	class Subject;

	class Observer
	{
	public:

		virtual ~Observer();

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		void ChangeSubject(Subject* const subject);

		virtual void OnNotify(GameObject* gameObj, EventID eventID) = 0;

	protected:

		explicit Observer(Subject* const subject);

	private:

		Subject* m_pSubject;

	};
}

#endif // !OBSERVER_H